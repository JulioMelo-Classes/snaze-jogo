#include "SnakeGame.hpp"

#include <chrono>  //por causa do sleep
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>  //por causa do sleep

#include "Player.hpp"

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"

using namespace std;

SnakeGame::SnakeGame(string levels, string mode, string ia) {
    m_levels_file = levels;
    m_modo = mode;
    m_ia = ia;
    m_choice = "";
    m_frameCount = 0;
    carrega_niveis();
    initialize_game();
}

void SnakeGame::carrega_niveis() {
    ifstream levelFile(m_levels_file);
    int lineCount = 0, linhas, colunas, comidas;
    string line;
    vector<string> level;
    while (!levelFile.eof()) {
        getline(levelFile, line);
        level.push_back(line);
        // 15 10 4
        stringstream ss;
        ss << line;  // Recebe a linha em ss e dps distribui para cada variável
        ss >> linhas;
        ss >> colunas;
        ss >> comidas;

        if (isdigit(line[0])) {
            lineCount++;
            for (int i = 0; i < linhas; i++) {
                getline(levelFile, line);
                level.push_back(line);
            }
            m_niveis.push_back(level);
            level.clear();
        }
    }
}

vector<string> SnakeGame::carrega_maze(vector<vector<string>> niveis, int n) {
    int count = 0;
    string vetor;
    for (auto vetor : niveis) {
        if (count == n) {
            return vetor;
        }
        count++;
    }
}

void SnakeGame::initialize_game() {
    // m_l = m_level->get_init_linha();
    // m_c = m_level->get_init_coluna();

    // carrega o nivel ou os níveis

    m_level = new Level(carrega_maze(m_niveis, m_nivel));
    m_state = WAITING_USER;  // estado inicial é WAITING_USER, mas poderia ser outro
    m_ia_player = Player();
    if (m_ia == "random") {
        if (m_modo == "pacmaze") {
            m_pacman = new Pacman(m_level->get_init_linha(), m_level->get_init_coluna());
        } else if (m_modo == "snaze") {
            cout << "teste" << endl;
        }
    }
    m_level->colocar_comida_teste();
}

void SnakeGame::process_actions() {
    // processa as entradas do jogador de acordo com o estado do jogo
    // nesse exemplo o jogo tem 3 estados, WAITING_USER, RUNNING e GAME_OVER.
    // no caso deste trabalho temos 2 tipos de entrada, uma que vem da classe Player, como resultado do processamento da IA
    // outra vem do próprio usuário na forma de uma entrada do teclado.
    switch (m_state) {
        case WAITING_USER:  // o jogo bloqueia aqui esperando o usuário digitar a escolha dele
            break;
        case WAITING_IA:
            m_ia_player.find_solution(m_level, m_pacman);
            m_action = m_ia_player.next_move();
            break;
        case WINNER:
            while (1) {
                cin >> m_decisao_jogador;
                if (m_decisao_jogador == 1) {
                    // Passou no loop
                    break;
                } else {
                    cout << "Escolha Inválida." << endl;
                }
            }
            break;
        default:
            // nada pra fazer aqui
            break;
    }
}

void SnakeGame::update() {
    // atualiza o estado do jogo de acordo com o resultado da chamada de "process_actions"
    switch (m_state) {
        case RUNNING:
            // if(m_frameCount>0 && m_frameCount%10 == 0) //depois de 10 frames o jogo pergunta se o usuário quer continuar
            //     m_state = WAITING_USER;
            /*atualiza a posição do Snake de acordo com a escolha*/
            if (m_action == 0) {  // up
                m_pacman->set_grafico('v');
                m_pacman->move(-1, 0);

            } else if (m_action == 1) {  // down
                m_pacman->set_grafico('^');
                m_pacman->move(1, 0);
            } else if (m_action == 2) {  // right
                m_pacman->set_grafico('<');
                m_pacman->move(0, 1);
            } else {  // left
                m_pacman->set_grafico('>');
                m_pacman->move(0, -1);
            }
            if (!m_level->permitido(m_pacman->get_pos())) {
                m_state = LOSE_LIFE;
            }
            m_level->verifica_comida(m_pacman->get_pos());
            if (m_level->verifica_comida(m_pacman->get_pos()) == true) {
                m_level->apagar_comida(m_pacman->get_pos());
                m_level->colocar_comida_teste();
                // m_level->colocar_comida();
                m_pacman->set_m_qnt_comida();
                if (m_pacman->get_qnt_comida() == m_level->get_comidas()) {
                    m_state = WINNER;
                }
            }
            // sempre depois de executar "running" uma vez
            // o jogo pergunta para a IA qual sua escolha
            if (m_state == RUNNING)  // se ainda form running (não pediu para esperar pelo user)
                m_state = WAITING_IA;
            break;
        case WAITING_USER:  // se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
            if (m_choice == "n") {
                m_state = GAME_OVER;
                game_over();
            } else {
                // pode fazer alguma coisa antes de fazer isso aqui
                m_state = WAITING_IA;
            }
            break;
        case WAITING_IA:  // Esperando pela IA
            /*alguma coisa aqui*/
            m_state = RUNNING;  // depois de processar coisas da IA sempre passa para Running
            break;
        case LOSE_LIFE:
            m_pacman->set_vidas(m_pacman->get_vidas() - 1);
            m_pacman->set_pos(make_pair(m_level->get_init_linha(), m_level->get_init_coluna()));
            if (m_pacman->get_vidas() == 0) {
                m_state = GAME_OVER;
                game_over();
            } else {
                m_state = WAITING_IA;
            }
            break;
        case WINNER:
            m_state = RUNNING;
        default:
            // nada pra fazer aqui
            break;
    }
}

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar
 */
void wait(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal
 */
void clearScreen() {
// some C++ voodoo here ;D
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}

void SnakeGame::render() {
    clearScreen();
    switch (m_state) {
        case WAITING_IA:
        case RUNNING:
            // desenha todas as linhas do labirinto
            int pos_l, pos_c;
            pos_l = m_pacman->get_pos().first;
            pos_c = m_pacman->get_pos().second;
            cout << "Vidas: " << m_pacman->mostrar_vidas() << " | ";
            cout << "Comidas: " << m_pacman->get_qnt_comida() << " de " << m_level->get_comidas() << endl;
            for (int i = 0; i < m_level->get_linhas(); i++) {
                for (int j = 0; j < m_level->get_colunas(); j++) {
                    if (i == pos_l && j == pos_c)
                        cout << m_pacman->get_grafico();
                    else
                        cout << m_level->get_maze_element(i, j);
                }
                cout << endl;
            }
            cout << "Linha: " << pos_l << " | ";
            cout << "Coluna: " << pos_c << " | FrameCount: " << m_frameCount << endl;
            break;
        case WAITING_USER:
            // carrega_niveis();
            cout << GRN " ---> Welcome to the classic Snake Game <--- " << endl;
            cout << GRN "          copyright DIMAp/UFRN 2017 " << endl;
            cout << GRN "-------------------------------------------------------" << endl;
            cout << GRN " Levels loaded: ";
            cout << RED "3";
            cout << GRN " | Snake lives: ";
            cout << RED "5";
            cout << GRN " | Apples to eat: ";
            cout << RED << m_level->get_comidas();
            cout << endl;
            cout << GRN " Clear all levels to win the game. Good luck!!! " << endl;
            cout << GRN "-------------------------------------------------------" << endl;
            cout << NC ">>> Press <ENTER> to start the game!" << endl;
            cout << endl;
            cout << GRN "Lives: ";
            cout << CYN << m_pacman->mostrar_vidas();
            cout << GRN " | Score: ";
            cout << GRN " | Food eaten: ";
            cout << CYN << m_pacman->get_qnt_comida();
            cout << GRN " de ";
            cout << CYN << m_level->get_comidas();
            cout << endl;
            cout << GRN "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
            for (auto item : m_niveis[0]) {
                cout << item << endl;
            }
            cout << GRN "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
            cin.ignore();
            m_choice = "s";
            break;
        case LOSE_LIFE:
            cout << "\nPerdeu uma vida!!" << endl;
            wait(400);
            break;
        case GAME_OVER:
            cout << "O jogo terminou!" << endl;
            break;
        case WINNER:
            cout << "Você conseguiu comer todos as comidas.\nPróximo nível!!!" << endl;
            cout << "[1] Ir para o próximo nível." << endl;
            cout << "[2] Reiniciar este nível." << endl;
            cout << "[3] Reiniciar o jogo a partir do nível 1." << endl;
            break;
            delete m_level;
            // PRÓXIMO NÍVEL
            m_level = new Level(carrega_maze(m_niveis, m_nivel + 1));
            break;
    }
    m_frameCount++;
}

void SnakeGame::game_over() {
    delete m_pacman;
    delete m_level;
}

void SnakeGame::loop() {
    render();  // chama um render para a interface inicial
    while (m_state != GAME_OVER) {
        process_actions();
        update();
        render();
        wait(300);  // espera 1 segundo entre cada frame
    }
}

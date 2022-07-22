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
    load_levels();
    initialize_game();
}

void SnakeGame::load_levels() {
    ifstream levelFile(m_levels_file);
    if (!levelFile.is_open()) {
        cout << "Erro! Arquivo inexistente." << endl;
        exit(-1);
    }
    int lineCount = 0, linhas, colunas, comidas;
    string line;
    vector<string> level;
    while (!levelFile.eof()) {
        getline(levelFile, line);
        level.push_back(line);
        stringstream ss;
        ss << line;  // Recebe a linha em ss e dps distribui para cada variável
        ss >> linhas;
        ss >> colunas;
        ss >> comidas;

        bool player_existe = false;

        if (isdigit(line[0])) {
            lineCount++;
            for (int i = 0; i < linhas; i++) {
                if (line.find("<") != string::npos) {
                    player_existe = true;
                }
                getline(levelFile, line);
                level.push_back(line);
            }
            m_niveis.push_back(level);
            if (player_existe == false) {
                cout << "Erro! Não foi encontrado nenhum ponto inicial do player no mapa " << m_niveis.size() << "." << endl;
                exit(-1);
            }
            level.clear();
        }
    }
    levelFile.close();
}

vector<string> SnakeGame::get_level(vector<vector<string>> &niveis, int n) {
    return niveis[n];
}

void SnakeGame::initialize_game() {
    // carrega o nivel ou os níveis
    m_level = new Level(get_level(m_niveis, m_nivel));
    m_state = WAITING_USER;  // estado inicial é WAITING_USER, mas poderia ser outro
    m_ia_player = Player();
    m_pacman = new Pacman(m_level->get_init_linha(), m_level->get_init_coluna());
    m_ia_player.set_pos_visitadas(m_pacman->get_pos());
    // m_level->colocar_comida_teste(m_ia_player.get_pos_atual());
    m_level->colocar_comida();
}

void SnakeGame::process_actions() {
    // processa as entradas do jogador de acordo com o estado do jogo
    switch (m_state) {
        case WAITING_USER:  // o jogo bloqueia aqui esperando o usuário digitar alguma coisa.
            getline(cin, m_choice);
            break;
        case WAITING_IA:
            if (m_modo == "pacmaze") {  // Estilo de jogo pacmaze.
                m_ia_player.find_solution(m_level, m_pacman);
                // m_ia_player.find_solution_plus(m_level->get_maze(), m_pacman->get_pos().first, m_pacman->get_pos().second);
                m_action = m_ia_player.next_move(m_level, m_pacman, m_ia);
            } else {  // Estilo de jogo snaze.
                cout << "teste" << endl;
            }
            break;
        case NEXT_LEVEL:
            cin >> m_decisao_jogador;  // Recebe a decisão do jogador após concluir um nível.
            break;
        case WINNER:
            cin >> m_decisao_jogador;  // Recebe a decisão do jogador após concluir um nível.
            break;
        case PRE_GAME_OVER:
            cin >> m_decisao_jogador;  // Recebe a decisão do jogador após concluir um nível.
            break;
        case LOSE_LIFE:
            cin >> m_continue;  // Recebe a decisão do jogador após colidir com algo.
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

            m_ia_player.set_pos_visitadas(m_pacman->get_pos());

            if (!m_level->permitido(m_pacman->get_pos())) {
                m_state = LOSE_LIFE;
            }

            m_ia_player.set_pos_atual(m_pacman->get_pos());

            if (m_ia_player.encontrou(m_level->get_pos_comida().first, m_level->get_pos_comida().second) == true) {
                m_pacman->comeu();
                m_level->comeu_pontos();
                m_pontos_totais += 10;
                m_level->apagar_comida(m_pacman->get_pos());
                // m_level->colocar_comida_teste(m_ia_player.get_pos_atual());
                m_level->colocar_comida();

                if (m_pacman->get_qnt_comida() == m_level->get_comidas()) {  // Verifica se comeu.
                    if (m_niveis.size() == m_count2) {                       // Verifica se a quantidade de mapas corresponde ao contador de mapas concluídos.

                        m_state = WINNER;  // Se sim, acabou o jogo e você ganhou.
                    } else {
                        m_state = NEXT_LEVEL;  // Se não, próximo mapa.
                    }
                }
            }
            // sempre depois de executar "running" uma vez
            // o jogo pergunta para a IA qual sua escolha
            if (m_state == RUNNING)  // se ainda form running (não pediu para esperar pelo user)
                m_state = WAITING_IA;
            break;

        case WAITING_USER:  // se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
            if (m_choice.empty()) {
                m_state = WAITING_IA;
            } else {
                m_state = GAME_OVER;
                game_over();
            }
            break;
        case WAITING_IA:  // Esperando pela IA
            /*alguma coisa aqui*/
            m_state = RUNNING;  // depois de processar coisas da IA sempre passa para Running
            break;

        case LOSE_LIFE:
            if (m_continue == "n" || m_continue == "N"){
                m_state = GAME_OVER;
                game_over();
            } else {
                m_pacman->resetar_qnt_comida();
                m_level->resetar_pontos();
                m_pacman->set_vidas(m_pacman->get_vidas() - 1);
                m_pacman->set_pos(make_pair(m_level->get_init_linha(), m_level->get_init_coluna()));
                if (m_pacman->get_vidas() == 0) {
                    m_state = PRE_GAME_OVER;
                } else {
                    m_state = WAITING_IA;
                }
            }
            break;

        case NEXT_LEVEL:
            if (m_decisao_jogador == 1) {
                // Próximo Nível.
                m_count2++;  // Atualiza contador de mapas concluídos.
                delete m_level;
                m_nivel += 1;  // Incrementa o contador de niveis, para ir para o próximo mapa.
                m_level = new Level(get_level(m_niveis, m_nivel));
                m_pacman->set_pos(make_pair(m_level->get_init_linha(), m_level->get_init_coluna()));
                m_pacman->resetar_qnt_comida();
                // m_level->colocar_comida_teste(m_ia_player.get_pos_atual());
                m_level->colocar_comida();
                m_state = WAITING_IA;
                break;
            } else if (m_decisao_jogador == 2) {
                // Reiniciar o mesmo nível.
                m_pontos_totais -= m_level->get_pontos();
                delete m_level;
                m_level = new Level(get_level(m_niveis, m_nivel));
                m_pacman->set_pos(make_pair(m_level->get_init_linha(), m_level->get_init_coluna()));
                m_pacman->resetar_qnt_comida();
                // m_level->colocar_comida_teste(m_ia_player.get_pos_atual());
                m_level->colocar_comida();
                m_state = WAITING_IA;
                break;
            } else if (m_decisao_jogador == 3) {
                game_over();
                m_state = GAME_OVER;
                break;
            } else {
                cout << "Invalid choice!" << endl;
                m_state = NEXT_LEVEL;
                break;
            }
            break;

        case WINNER:
            if (m_decisao_jogador == 1) {
                // Reiniciar o mesmo nível.
                m_pontos_totais -= m_level->get_pontos();
                delete m_level;
                m_level = new Level(get_level(m_niveis, m_nivel));
                m_pacman->set_pos(make_pair(m_level->get_init_linha(), m_level->get_init_coluna()));
                m_pacman->resetar_qnt_comida();
                // m_level->colocar_comida_teste(m_ia_player.get_pos_atual());
                m_level->colocar_comida();
                m_state = WAITING_IA;
                break;
            } else if (m_decisao_jogador == 2) {
                // Reiniciar a partir do lv 1.
                m_pontos_totais = 0;
                delete m_level;
                m_count2 = 1;  // Reinicia o contador de mapas concluídos.
                m_nivel = 0;   // Zera o nível, 0 = primeiro mapa.
                m_level = new Level(get_level(m_niveis, m_nivel));
                m_pacman->set_pos(make_pair(m_level->get_init_linha(), m_level->get_init_coluna()));
                m_pacman->resetar_qnt_comida();
                // m_level->colocar_comida_teste(m_ia_player.get_pos_atual());
                m_level->colocar_comida();
                m_state = WAITING_IA;
                break;
            } else if (m_decisao_jogador == 3) {
                game_over();
                m_state = GAME_OVER;
                break;
            } else {
                cout << "Invalid choice!" << endl;
                m_state = WINNER;
                break;
            }
            break;

        case PRE_GAME_OVER:
            m_pacman->set_vidas(5);
            if (m_decisao_jogador == 1) {
                // Reiniciar o mesmo nível.
                m_pontos_totais -= m_level->get_pontos();
                delete m_level;
                m_level = new Level(get_level(m_niveis, m_nivel));
                m_pacman->set_pos(make_pair(m_level->get_init_linha(), m_level->get_init_coluna()));
                m_pacman->resetar_qnt_comida();
                // m_level->colocar_comida_teste(m_ia_player.get_pos_atual());
                m_level->colocar_comida();
                m_state = WAITING_IA;
                break;
            } else if (m_decisao_jogador == 2) {
                // Reiniciar a partir do lv 1.
                m_pontos_totais = 0;
                delete m_level;
                m_count2 = 1;  // Reinicia o contador de mapas concluídos.
                m_nivel = 0;   // Zera o nível, 0 = primeiro mapa.
                m_level = new Level(get_level(m_niveis, m_nivel));
                m_pacman->set_pos(make_pair(m_level->get_init_linha(), m_level->get_init_coluna()));
                m_pacman->resetar_qnt_comida();
                // m_level->colocar_comida_teste(m_ia_player.get_pos_atual());
                m_level->colocar_comida();
                m_state = WAITING_IA;
                break;
            } else if (m_decisao_jogador == 3) {
                // delete m_level;
                m_state = GAME_OVER;
                game_over();
                break;
            } else {
                cout << "Invalid choice!" << endl;
                m_state = PRE_GAME_OVER;
                break;
            }
            break;
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
    int aux = 0, fix_render_start;
    switch (m_state) {
        case WAITING_IA:
        case RUNNING:
            rodando_tela();
            break;
        case WAITING_USER:
            primeira_tela();
            break;
        case LOSE_LIFE:
            cout << RED "\nLost a life!!" << endl;
            wait(600);
            cout << "Do you want to continue (Yes/No)? ";
            break;
        case PRE_GAME_OVER:
            pre_gameover_tela();
            break;
        case NEXT_LEVEL:
            next_level_tela();
            break;
        case WINNER:
            winner_tela();
            break;
        case GAME_OVER:
            cout << "Thanks for playing!" << endl;
            break;
    }
    //cout << RED << "\n --- > FRAME COUNT >> " << m_frameCount << endl;
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
        wait(5);  // espera 1 segundo entre cada frame
    }
}

void SnakeGame::primeira_tela() {
    int aux = 0;
    cout << GRN " ---> Welcome to the classic Snake Game <--- " << endl;
    // cout << GRN "          copyright DIMAp/UFRN 2017 " << endl;
    cout << GRN "-------------------------------------------------------" << endl;
    cout << GRN " Levels loaded: ";
    cout << RED << m_niveis.size();
    cout << GRN " | Snake lives: ";
    cout << RED << m_pacman->get_vidas();
    cout << endl;
    cout << GRN " Clear all levels to win the game. Good luck!!! " << endl;
    cout << GRN "-------------------------------------------------------" << endl;
    cout << NC ">>> Press <ENTER> to start the game!" << endl;
    cout << endl;
    cout << GRN "Lives: ";
    cout << CYN << m_pacman->mostrar_vidas();
    cout << GRN " | Score: ";
    cout << CYN << m_pontos_totais;
    cout << GRN " | Apples eaten: ";
    cout << CYN << m_pacman->get_qnt_comida();
    cout << GRN " of ";
    cout << CYN << m_level->get_comidas();
    cout << endl;
    cout << GRN "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    for (auto item : m_niveis[0]) {
        aux++;
        if (aux > 1) {
            cout << item << endl;
        }
    }
    cout << GRN "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
}

void SnakeGame::next_level_tela() {
    cout << GRN "Congratulations !!!\nYou managed to eat all the foods." << endl;
    cout << GRN "[1] Go to the next level." << endl;
    cout << GRN "[2] Restart this level." << endl;
    cout << GRN "[3] End the game." << endl;
    cout << endl;
    cout << GRN "Choose an option: ";
}

void SnakeGame::rodando_tela() {
    cout << GRN "Lives: ";
    cout << RED << m_pacman->mostrar_vidas();
    cout << GRN " | Score: ";
    cout << CYN << m_pontos_totais;
    cout << GRN " | Apples eaten: ";
    cout << CYN << m_pacman->get_qnt_comida();
    cout << GRN " of ";
    cout << CYN << m_level->get_comidas() << endl;
    for (int i = 0; i < m_level->get_linhas(); i++) {
        for (int j = 0; j < m_level->get_colunas(); j++) {
            if (i == m_pacman->get_pos().first && j == m_pacman->get_pos().second) {
                cout << RED << m_pacman->get_grafico();
            } else {
                if (m_level->get_maze_element(i, j) == '*') {
                    cout << GRN << m_level->get_maze_element(i, j);
                } else {
                    cout << NC << m_level->get_maze_element(i, j);
                }
            }
        }
        cout << endl;
    }
}

void SnakeGame::winner_tela() {
    cout << GRN "Congratulations, you made it through all the levels!!!" << endl;
    cout << GRN "Your score: " << m_pontos_totais << endl;
    cout << GRN "[1] Restart this level." << endl;
    cout << GRN "[2] Restart the game from level 1." << endl;
    cout << GRN "[3] End the game." << endl
         << endl;
    cout << GRN "Choose an option:  ";
}

void SnakeGame::pre_gameover_tela() {
    cout << GRN "You lost all your lives..." << endl;
    cout << GRN "Your score: " << m_pontos_totais << endl;
    cout << GRN "[1] Restart this level." << endl;
    cout << GRN "[2] Restart the game from level 1." << endl;
    cout << GRN "[3] End the game." << endl
         << endl;
    cout << GRN "Choose an option: ";
}
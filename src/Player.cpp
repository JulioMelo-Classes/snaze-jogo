#include "Player.hpp"

#include <iostream>

using namespace std;

void Player::find_solution(Level *level, Pacman *pacman) {
    if (m_acoes.size() == 0) {
        // for(int i=0; i<4; i++)
        auto pos = pacman->get_pos();
        pos.first -= 1;  // up
        if (permitido(level->get_maze(), pos.first, pos.second)) {
            m_acoes.push_back(0);
            return;
        }

        pos = pacman->get_pos();
        pos.second += 1;  // right
        if (permitido(level->get_maze(), pos.first, pos.second)) {
            m_acoes.push_back(2);
            return;
        }

        pos = pacman->get_pos();
        pos.first += 1;  // down
        if (permitido(level->get_maze(), pos.first, pos.second)) {
            m_acoes.push_back(1);
            return;
        }

        pos = pacman->get_pos();
        pos.second -= 1;  // left
        if (permitido(level->get_maze(), pos.first, pos.second)) {
            m_acoes.push_back(3);
            return;
        } else {
            // Nao consegui ir pra nenhuma direção
            m_acoes.push_back(2);
        }
    }
    //"resolve o problema com base no mapa, a posição atual da cobra e a posição atual da comida"
}

bool Player::find_solution_plus(vector<string> level, int linha, int coluna){
    if (encontrou(linha, coluna)){
        return true;
    } else {
        if (permitido(level, linha + 1, coluna) == true && visitado(m_pos_visitadas, linha + 1, coluna) == false){
            if (find_solution_plus(level, linha + 1, coluna)){
                return true;
            }
        }

        if (permitido(level, linha - 1, coluna) == true && visitado(m_pos_visitadas, linha - 1, coluna) == false){
            if (find_solution_plus(level, linha - 1, coluna)){
                return true;
            }
        }

        if (permitido(level, linha, coluna + 1) == true && visitado(m_pos_visitadas, linha, coluna + 1) == false){
            if (find_solution_plus(level, linha, coluna + 1)){
                return true;
            }
        }

        if (permitido(level, linha, coluna - 1) == true && visitado(m_pos_visitadas, linha, coluna - 1) == false){
            if (find_solution_plus(level, linha, coluna - 1)){
                return true;
            }
        }
    }
    return false;
}

void Player::set_pos_atual(pair<int, int> pos){
    m_pos_atual = pos;
}

bool Player::encontrou(int linha, int coluna) {
    pair<int, int> aux;
    aux.first = linha; aux.second = coluna;
    if (m_pos_atual == aux) {
        return true;
    }
    return false;
}

bool Player::visitado(vector<pair<int, int>> pos_visitadas, int linha, int coluna){
    pair<int, int> pos;
    pos.first = linha; pos.second = coluna;
    for (auto par : pos_visitadas){
        if (pos == par){
            return true;
        }
    }
    return false;
}

bool Player::permitido(vector<string> level, int linha, int coluna) {
    int linhas = 0, colunas = 0;
    for (auto linha : level){
        for (auto caracter : linha){
            colunas++;
        }
        linhas++;
    }

    if (linha < 0 || coluna < 0)
        return false;

    if (linha >= linhas || coluna >= colunas)
        return false;

    if (level.at(linha).at(coluna) == '#')
        return false;

    return true;
}

int Player::next_move(Level *level, Pacman *pacman, string modo) {
    random_device random;
    default_random_engine dre(random());
    uniform_int_distribution<int> rand(0, 3);
    int aleatorio;
    // sorteia uma ação aleatória que não causa morte
    /*retorna uma ação aleatória entre 0 e 3*/
    int acao = m_acoes.front();
    m_acoes.erase(m_acoes.begin());

    if (modo == "random"){
        while (true) {
            auto pos = pacman->get_pos();
            bool pode = false;
            aleatorio = rand(dre);

            if (verifica_preso(level, pacman)) {
                // cout << "TÁ PRESO!!" << endl;
                // cin.ignore();
                break;
            }

            if (aleatorio == 0) {  // up
                pos.first -= 1;
                pode = permitido(level->get_maze(), pos.first, pos.second);
            } else if (aleatorio == 1) {  // down
                pos.first += 1;
                pode = permitido(level->get_maze(), pos.first, pos.second);
            } else if (aleatorio == 2) {  // right
                pos.second += 1;
                pode = permitido(level->get_maze(), pos.first, pos.second);
            } else if (aleatorio == 3) {  // left
                pos.second -= 1;
                pode = permitido(level->get_maze(), pos.first, pos.second);
            }

            if (pode == true) {
                break;
            }
        }
        
    }
    return aleatorio;
}

bool Player::verifica_preso(Level *level, Pacman *pacman) {
    bool pode = false;
    int posicoes = 0, fix = 0;

    auto pos = pacman->get_pos();
    pos.first -= 1;
    permitido(level->get_maze(), pos.first, pos.second) ? fix++ : posicoes++;

    pos = pacman->get_pos();
    pos.first += 1;
    permitido(level->get_maze(), pos.first, pos.second) ? fix++ : posicoes++;

    pos = pacman->get_pos();
    pos.second += 1;
    permitido(level->get_maze(), pos.first, pos.second) ? fix++ : posicoes++;

    pos = pacman->get_pos();
    pos.second -= 1;
    permitido(level->get_maze(), pos.first, pos.second) ? fix++ : posicoes++;

    if (posicoes == 4) {
        return true;
    }
    return pode;
}

void Player::set_pos_visitadas(pair<int, int> pos){
    m_pos_visitadas.push_back(pos);
}

void Player::get_tam(){
    cout << m_pos_visitadas.size() << endl;
}

pair<int, int> Player::get_pos_atual(){
    return m_pos_atual;
}
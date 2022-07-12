#include "Player.hpp"

#include <iostream>

using namespace std;

void Player::find_solution(Level *level, Pacman *pacman) {
    if (m_acoes.size() == 0) {
        // for(int i=0; i<4; i++)
        auto pos = pacman->get_pos();
        pos.first -= 1;  // up
        if (level->permitido(pos)) {
            m_acoes.push_back(0);
            return;
        }

        pos = pacman->get_pos();
        pos.second += 1;  // right
        if (level->permitido(pos)) {
            m_acoes.push_back(2);
            return;
        }

        pos = pacman->get_pos();
        pos.first += 1;  // down
        if (level->permitido(pos)) {
            m_acoes.push_back(1);
            return;
        }

        pos = pacman->get_pos();
        pos.second -= 1;  // left
        if (level->permitido(pos)) {
            m_acoes.push_back(3);
            return;
        }
    }
    //"resolve o problema com base no mapa, a posição atual da cobra e a posição atual da comida"
}

int Player::next_move() {
    random_device random;
    default_random_engine dre(random());
    uniform_int_distribution<int> rand(0, 3);
    int aleatorio = rand(dre);
    // sorteia uma ação aleatória que não causa morte
    /*retorna uma ação aleatória entre 0 e 3*/
    int acao = m_acoes.front();
    m_acoes.erase(m_acoes.begin());
    return aleatorio;
}
#include "Player.hpp"

#include <iostream>

using namespace std;

void Player::find_solution(Level *level, Snake *snake) {
    if (m_acoes.size() == 0) {
        // for(int i=0; i<4; i++)
        auto pos = snake->get_pos();
        pos.first -= 1;  // up
        if (level->permitido(pos)) {
            m_acoes.push_back(0);
            return;
        }

        pos = snake->get_pos();
        pos.second += 1;  // right
        if (level->permitido(pos)) {
            m_acoes.push_back(2);
            return;
        }

        pos = snake->get_pos();
        pos.first += 1;  // down
        if (level->permitido(pos)) {
            m_acoes.push_back(1);
            return;
        }

        pos = snake->get_pos();
        pos.second -= 1;  // left
        if (level->permitido(pos)) {
            m_acoes.push_back(3);
            return;
        }
    }
    //"resolve o problema com base no mapa, a posição atual da cobra e a posição atual da comida"
}

int Player::next_move() {
    // sorteia uma ação aleatória que não causa morte
    /*retorna uma ação aleatória entre 0 e 3*/
    int acao = m_acoes.front();
    m_acoes.erase(m_acoes.begin());
    return acao;
}
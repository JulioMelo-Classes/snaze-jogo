#include "Snake.hpp"
using namespace std;

Snake::Snake(int linha_inicial, int coluna_inicial) {
    m_vidas = 5;
    m_posl = linha_inicial;
    m_posc = coluna_inicial;
    m_grafico = 'c';
}

int Snake::get_vidas() {
    return m_vidas;
}

void Snake::set_vidas(int vidas) {
    m_vidas = vidas;
}

pair<int, int> Snake::get_pos() {
    return make_pair(m_posl, m_posc);
}

void Snake::set_pos(pair<int, int> pos) {
    m_posl = pos.first;
    m_posc = pos.second;
}

char Snake::get_grafico() {
    return m_grafico;
}

void Snake::move(int l, int c) {
    m_posl += l;
    m_posc += c;
}

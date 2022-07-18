#include "Pacman.hpp"
using namespace std;

Pacman::Pacman(int linha_inicial, int coluna_inicial) {
    m_vidas = 5;
    m_posl = linha_inicial;
    m_posc = coluna_inicial;
    m_grafico = 'c';
}

int Pacman::get_vidas() {
    return m_vidas;
}

void Pacman::set_vidas(int vidas) {
    m_vidas = vidas;
}

pair<int, int> Pacman::get_pos() {
    return make_pair(m_posl, m_posc);
}

void Pacman::set_pos(pair<int, int> pos) {
    m_posl = pos.first;
    m_posc = pos.second;
}

char Pacman::get_grafico() {
    return m_grafico;
}

void Pacman::move(int l, int c) {
    m_posl += l;
    m_posc += c;
}

string Pacman::mostrar_vidas() {
    string coracoes = "";
    for (int i = 0; i < get_vidas(); i++) {
        coracoes.append("❤️ ");
    }
    return coracoes;
}

void Pacman::set_grafico(char character) {
    m_grafico = character;
}

void Pacman::resetar_qnt_comida() {
    m_qnt_comida = 0;
}

void Pacman::comeu() {
    m_qnt_comida += 1;
}

int Pacman::get_qnt_comida() {
    return m_qnt_comida;
}
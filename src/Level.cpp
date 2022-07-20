#include "Level.hpp"

#include <fstream>
#include <sstream>
using namespace std;

Level::Level(vector<string> nivel) {
    int lineCount = 0;
    for (auto line : nivel) {
        if (isdigit(line[0])) {
            stringstream ss;
            ss << line;  // Recebe a linha em ss e dps distribui para cada variável
            ss >> m_linhas;
            ss >> m_colunas;
            ss >> m_comidas;
        } else {
            if (line.find("<") != string::npos) {
                /*encontra a posição inicial de acordo com o mapa*/
                m_init_linha = lineCount;
                m_init_coluna = line.find("<");
                line[m_init_coluna] = ' ';
            }
            m_maze.push_back(line);
            lineCount++;
        }
    }
}

void Level::colocar_comida_teste(pair<int, int> pos) {
    m_pos_comida = make_pair(pos.first, pos.second + 1);
    m_maze[pos.first][pos.second + 1] = '*';
}

void Level::colocar_comida() {
    random_device random1;
    random_device random2;
    default_random_engine drl(random1());
    default_random_engine drc(random2());
    uniform_int_distribution<int> linha(1, m_linhas - 1);
    uniform_int_distribution<int> coluna(1, m_colunas - 1);
    while (true) {
        int linha_comida = linha(drl);
        int coluna_comida = coluna(drc);
        if ((get_maze_element(linha_comida, coluna_comida) != '#') && (get_maze_element(linha_comida, coluna_comida) != '.')) {
            m_pos_comida = make_pair(linha_comida, coluna_comida);
            m_maze[linha_comida][coluna_comida] = '*';
            m_pos_comida = make_pair(linha_comida, coluna_comida);
            break;
        }
    }
}

void Level::comeu_pontos() {
    m_pontuacao += 10;
}

int Level::get_pontos() {
    return m_pontuacao;
}

void Level::resetar_pontos() {
    m_pontuacao = 0;
}

void Level::apagar_comida(pair<int, int> posicao) {
    m_maze[posicao.first][posicao.second] = ' ';
}

int Level::get_init_linha() {
    return m_init_linha;
}

int Level::get_init_coluna() {
    return m_init_coluna;
}

pair<int, int> Level::get_pos_comida() {
    return m_pos_comida;
}

int Level::get_comidas() {
    return m_comidas;
}

int Level::get_linhas() {
    return m_linhas;
}

int Level::get_colunas() {
    return m_colunas;
}

char Level::get_maze_element(int l, int c) {
    return m_maze.at(l).at(c);
}

vector<string> Level::get_maze() {
    return m_maze;
}

bool Level::permitido(std::pair<int, int> pos) {
    if (pos.first < 0 || pos.second < 0)
        return false;

    if (pos.first >= m_linhas || pos.second >= m_colunas)
        return false;

    if (m_maze.at(pos.first).at(pos.second) == '#')
        return false;

    return true;
}
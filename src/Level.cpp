#include <fstream>
#include <sstream>

#include "Level.hpp"
using namespace std;


Level::Level(string level_file){
    ifstream levelFile(level_file); 
    int lineCount = 0;
    string line;
    if(levelFile.is_open()){
        getline(levelFile, line);
        //15 10 4
        stringstream ss;
        ss<<line; // Recebe a linha em ss e dps distribui para cada variável
        ss>>m_linhas;
        ss>>m_colunas;
        ss>>m_comidas;
        
        while(getline(levelFile, line)){ //pega cada linha do arquivo
            if(line.find("v") != string::npos){
                /*encontra a posição inicial de acordo com o mapa*/
                m_init_linha = lineCount;
                m_init_coluna = line.find("v");
                line[m_init_coluna] = ' ';
            }
            m_maze.push_back(line);
            lineCount++;
        }
    }
}

int Level::get_init_linha(){
    return m_init_linha;
}

int Level::get_init_coluna(){
    return m_init_coluna;
}

int Level::get_linhas(){
    return m_linhas;
}

int Level::get_colunas(){
    return m_colunas;
}

char Level::get_maze_element(int l, int c){
    return m_maze.at(l).at(c);
}

bool Level::permitido(std::pair<int,int> pos){
    if(pos.first < 0 || pos.second < 0)
        return false;
    
    if(pos.first >= m_linhas || pos.second >= m_colunas)
        return false;

    if(m_maze.at(pos.first).at(pos.second) == '#')
        return false;

    return true;
}
#ifndef Level_hpp
#define Level_hpp
#include <iostream>
#include <utility>
#include <vector>

class Level {
   private:
    int m_linhas, m_colunas, m_comidas;
    int m_init_linha, m_init_coluna;
    std::pair<int, int> m_pos_comida;
    std::vector<std::string> m_maze;

   public:
    Level(std::string level_file);

    int get_init_linha();
    int get_init_coluna();
    std::pair<int, int> get_pos_comida();
    int get_comidas();
    void set_comidas(int comidas);
    void colocar_comida();
    int get_linhas();
    int get_colunas();

    char get_maze_element(int l, int c);

    bool permitido(std::pair<int, int> pos);
};
#endif  // Level_hpp

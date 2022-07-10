#ifndef Level_hpp
#define Level_hpp
<<<<<<< Updated upstream

class Level {

};

#endif
=======
#include <vector>
#include <iostream>


class Level{
    private:
        int m_linhas, m_colunas, m_comidas;
        int m_init_linha, m_init_coluna;
        std::vector<std::string> m_maze;
    public:
        Level(std::string level_file);

        int get_init_linha();
        int get_init_coluna();

        int get_linhas();
        int get_colunas();

        char get_maze_element(int l, int c);
};
#endif //Level_hpp
>>>>>>> Stashed changes

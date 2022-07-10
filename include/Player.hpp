#ifndef Player_hpp
#define Player_hpp
#include <vector>
#include "Level.hpp"
#include "Snake.hpp"

class Player{
    private:
        std::vector<int> m_acoes;
    public:
        void find_solution(Level *level, Snake *snake);
        /**
         * Retorna a próxima ação do jogador um mapeamento de 0-3, representando ir para esquerda, cima, direita, baixo
         * @return a próxima ação do jogador
         **/
        int next_move();
};
#endif //Player_hpp
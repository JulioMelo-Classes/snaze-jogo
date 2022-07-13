#ifndef Player_hpp
#define Player_hpp
#include <vector>
#include "Level.hpp"
#include "Pacman.hpp"

class Player{
    private:
        std::vector<int> m_acoes;
    public:
        void find_solution(Level *level, Pacman *pacman);
        /**
         * Retorna a próxima ação do jogador um mapeamento de 0-3, representando ir para esquerda, cima, direita, baixo
         * @return a próxima ação do jogador
         **/
        int next_move(Level *level, Pacman *pacman);

        bool verifica_preso(Level *level, Pacman *pacman);
};
#endif //Player_hpp
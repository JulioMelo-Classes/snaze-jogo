#ifndef Player_hpp
#define Player_hpp
#include <vector>
#include "Level.hpp"
#include "Pacman.hpp"

class Player{
    private:
        std::vector<int> m_acoes; //<! Vetor com as ações a serem realizadas pelo jogador.
    public:
        void find_solution(Level *level, Pacman *pacman);
        /**
         * Retorna a próxima ação do jogador um mapeamento de 0-3, representando ir para esquerda, cima, direita, baixo
         * @return a próxima ação do jogador
         **/
        int next_move(Level *level, Pacman *pacman);

        /**
         * @brief Verifica se o jogador está preso nas 4 direções, caso esteja, irá se mover para alguma direção
         * que ocorrerá em uma morte proposital.
         */
        bool verifica_preso(Level *level, Pacman *pacman);
};
#endif //Player_hpp
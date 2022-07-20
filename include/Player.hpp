#ifndef Player_hpp
#define Player_hpp
#include <vector>

#include "Level.hpp"
#include "Pacman.hpp"

class Player {
   private:
    std::vector<int> m_acoes;  //<! Vetor com as ações a serem realizadas pelo jogador.
    std::vector<std::pair<int, int>> m_pos_visitadas;
    std::pair<int, int> m_pos_atual;

   public:
    void find_solution(Level *level, Pacman *pacman);
    /**
     * Retorna a próxima ação do jogador um mapeamento de 0-3, representando ir para esquerda, cima, direita, baixo
     * @return a próxima ação do jogador
     **/
    int next_move(Level *level, Pacman *pacman, std::string modo);

    /**
     * @brief Verifica se o jogador está preso nas 4 direções, caso esteja, irá se mover para alguma direção
     * que ocorrerá em uma morte proposital.
     */
    bool verifica_preso(Level *level, Pacman *pacman);

    void set_pos_visitadas(std::pair<int, int> pos);

    void set_pos_atual(std::pair<int, int> pos);

    bool visitado(std::vector<std::pair<int, int>> pos_visitadas, int linha, int coluna);

    bool find_solution_plus(std::vector<std::string> level, int linha, int coluna);

    /**
     * @brief Compara a posição do jogador com a posição da comida no mapa, caso ambas as posições
     * sejam igual significa que o jogador comeu a comida.
     */
    bool encontrou(int linha, int coluna);

    void get_tam();

    std::pair<int, int> get_pos_atual();

    /**
     * @brief Verifica se a posição inserida nos parâmetros é uma posição válida no mapa, ou seja, que
     * não é uma parede.
     */
    bool permitido(std::vector<std::string> level, int linha, int coluna);

    bool permitido1(std::pair<int, int> pos);
};
#endif  // Player_hpp
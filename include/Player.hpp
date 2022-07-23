#ifndef Player_hpp
#define Player_hpp
#include <vector>

#include "Level.hpp"
#include "Pacman.hpp"

class Player {
   private:
    std::vector<int> m_acoes;  //<! Vetor com as ações a serem realizadas pelo jogador.
    // ATRIBUTOS DE SUPORTE A UTILIZAÇÃO DO FIND, NÃO IMPLEMENTADO.
    std::vector<std::pair<int, int>> m_pos_visitadas;  //<! Vetor com as posições marcadas como visitadas.
    std::pair<int, int> m_pos_atual;                   //<! Posição atual do jogador.

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

    /**
     * @brief Compara a posição do jogador com a posição da comida no mapa, caso ambas as posições
     * sejam igual significa que o jogador comeu a comida.
     */
    bool encontrou(int linha, int coluna);

    // FUNÇÕES DE SUPORTE A UTILIZAÇÃO DO FIND, NÃO IMPLEMENTADO.

    /**
     * @brief Marca como uma posição visitada para utilização do find.
     */
    void set_pos_visitadas(std::pair<int, int> pos);

    /**
     * @brief Define a posição atual para utilização do find.
     */
    void set_pos_atual(std::pair<int, int> pos);

    /**
     * @brief Retorna true se a posição já estiver tido marcada como visitado
     */
    bool visitado(std::vector<std::pair<int, int>> pos_visitadas, int linha, int coluna);

    /**
     * @brief Implementação do find (não conseguimos)
     */
    bool find_solution_plus(std::vector<std::string> level, int linha, int coluna);

    /**
     * @brief  Retorna quantas posições já foram marcadas como visitadas.
     */
    void get_tam();

    std::pair<int, int> get_pos_atual();
};
#endif  // Player_hpp
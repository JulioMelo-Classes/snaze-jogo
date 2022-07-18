#ifndef Level_hpp
#define Level_hpp
#include <iostream>
#include <random>
#include <utility>
#include <vector>

class Level {
   private:
    int m_linhas, m_colunas, m_comidas;  //<! Variáveis que armazenam as informações iniciais de um mapa.
    int m_init_linha, m_init_coluna;     //<! Posições iniciais do player no mapa.
    std::pair<int, int> m_pos_comida;    //<! Posição da comida no mapa.
    std::vector<std::string> m_maze;     //<! O próprio mapa, construído com base em um arquivo .txt.

   public:
    Level(std::vector<std::string> nivel);

    /**
     * @brief Posição na linha onde o jogador irá nascer.
     */
    int get_init_linha();

    /**
     * @brief Posição na coluna onde o jogador irá nascer.
     */
    int get_init_coluna();

    /**
     * @brief Retorna a posição da comida em linha e coluna no mapa.
     */
    // std::pair<int, int> get_pos_comida();

    /**
     * @brief Quantidade de comidas totais necessárias para completar aquele mapa.
     */
    int get_comidas();

    /**
     * @brief Sorteia uma posição aleatória válida no mapa e coloca uma comida.
     */
    void colocar_comida();

    /// FUNÇÃO PARA TESTE DE DESENVOLVIMENTO
    void colocar_comida_teste();

    /**
     * @brief Apaga o desenho de uma comida no mapa.
     */
    void apagar_comida(std::pair<int, int> posicao);

    /**
     * @brief Retorna o total de linhas do mapa.
     */
    int get_linhas();

    /**
     * @brief Retorna o total de colunas do mapa.
     */
    int get_colunas();

    /**
     * @brief Compara a posição do jogador com a posição da comida no mapa, caso ambas as posições
     * sejam igual significa que o jogador comeu a comida.
     */
    bool verifica_comida(std::pair<int, int> posicao);

    /**
     * @brief Retorna o elemento do mapa correspondente as posições inseridas nos parâmetros.
     */
    char get_maze_element(int l, int c);

    /**
     * @brief Verifica se a posição inserida nos parâmetros é uma posição válida no mapa, ou seja, que
     * não é uma parede.
     */
    bool permitido(std::pair<int, int> pos);
};
#endif  // Level_hpp

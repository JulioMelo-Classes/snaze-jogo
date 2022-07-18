#ifndef Pacman_hpp
#define Pacman_hpp
#include <iostream>

class Pacman {
   private:
    int m_posl, m_posc;    //<! Posições em linha e coluna do pacman no mapa.
    int m_vidas;           //<! Quantidade de vidas do pacman.
    char m_grafico;        //<! Caractere que representa o pacman no mapa.
    int m_qnt_comida = 0;  //<! Quantidade de comidas que o pacman conseguiu comer.

   public:
    /**
     * @brief Inicializa o jogador pacman com sua posição inicial e vidas.
     */
    Pacman(int linha_inicial, int coluna_inicial);

    /**
     * @brief Retorna um par contendo a posição atual em linha e coluna do pacman no mapa.
     */
    std::pair<int, int> get_pos();

    /**
     * @brief Define a posição inicial do pacman no mapa.
     * @param pos Par contendo as posições de linha e coluna respectivamente no mapa para o pacman.
     */
    void set_pos(std::pair<int, int> pos);

    /**
     * @brief Retorna a quantidade de vidas do pacman.
     */
    int get_vidas();

    /**
     * @brief Define a quantidade de vidas do pacman.
     */
    void set_vidas(int vidas);

    /**
     * @brief Retorna o caractere que representa o pacman no mapa.
     */
    char get_grafico();

    /**
     * @brief Define o caractere que representará o pacman no mapa.
     */
    void set_grafico(char character);

    /**
     * @brief Reseta a quantidade de comida para 0.
     * Útil quando o jogador vai jogar ou re-jogar um mapa.
     */
    void resetar_qnt_comida();

    /**
     * @brief Incremento de +1 em quantas comidas o pacman já comeu.
     */
    void comeu();

    /**
     * @brief Retorna qual a quantidade atual de comidas que o pacman comeu.
     */
    int get_qnt_comida();

    /**
     * @brief Movimenta o pacman no mapa.
     * @param l Quantidade de casas que ele irá se mover no eixo horizontal.
     * @param c Quantidade de casas que ele irá se mover no eixo vertical.
     */
    void move(int l, int c);

    /**
     * @brief Mostra as vidas atuais em unidades de corações.
     */
    std::string mostrar_vidas();
};
#endif
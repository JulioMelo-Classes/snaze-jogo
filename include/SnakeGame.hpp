#ifndef SnakeGame_hpp
#define SnakeGame_hpp
#include <iostream>
#include <vector>

#include "Level.hpp"
#include "Pacman.hpp"
#include "Player.hpp"

class SnakeGame {
   public:
    /**
     * @brief descreve os possíveis estados do jogo, fique à vontade para adicionar outros se necessário
     **/
    enum GameStates {
        RUNNING,       //<! quando o jogo está executando o estado é RUNNING
        GAME_OVER,     //<! quando o jogo deve terminar o estado é GAME_OVER
        WAITING_USER,  //<! quando o jogo deve esperar por uma entrada do usuário o estado é WAITING_USER
        WAITING_IA,    //<! usualmente o jogo está esperando por comandos da IA, neste caso o estado é WAITING_IA
        LOSE_LIFE,     //<! quando perde uma vida entra nesse estado
        WINNER         //<! quando o player consegue comer todas as comidas do mapa.
    };

   private:
    Level *m_level;  //<! representa o level atual
    Pacman *m_pacman;

    // int m_l, m_c; //representa a posição do Snake no exemplo da sala.
    //<! atributos adicione outros se quiser
    // std::vector<std::string> m_maze; //<! vector contendo o labirinto atual, pode ser interpretado como uma matriz
    int m_frameCount;                                //<! contador de frames, usado apenas como exemplo
    std::string m_choice;                            //<! usado na função process_actions para guardar a escolha do usuário
    GameStates m_state;                              //<! guarda o estado do jogo
    std::string m_levels_file;                       //<! arquivo com os níveis do jogo
    std::vector<std::vector<std::string>> m_niveis;  //<! vector com os niveis do jogo.
    std::string m_modo;                              //<! arquivo com os níveis do jogo
    std::string m_ia;                                //<! arquivo com os níveis do jogo
    Player m_ia_player;                              //<! instancia da classe Player responsável pela IA do jogo
    int m_decisao_jogador;                           //<! Representa a escolha do jogador após conseguir todas as comidas.
    int m_action;                                    //<! Representa a ação escolhida pela IA
    int m_nivel = 0;

   public:
    /**
     * @brief construtor padrão, fique à vontade para adicionar parâmetros se desejar
     **/
    SnakeGame(std::string levels, std::string mode, std::string ia);

    /**
     * @brief chamado no main, este loop executa o jogo indefinidamente até que o usuário escolha terminar!
     */
    void loop();

    void carrega_niveis();

    std::vector<std::string> carrega_maze(std::vector<std::vector<std::string>> &niveis, int n);

   private:
    /**
     * @brief realiza a inicialização geral do jogo, fique à vontade para adicionar parâmetros se achar que deve
     **/
    void initialize_game();

    /**
     * @brief atualiza o estado do jogo, basicamente movendo os objetos, sorteando novas posições de comida
     **/
    void update();

    /**
     * @brief processa as entradas do jogador
     **/
    void process_actions();

    /**
     * @brief testa o estado do jogo e desenha a tela correspondente
     **/
    void render();

    /**
     * @brief é chamada quando o jogo termina a fim de destruir/resetar elementos do estado do jogo
     **/
    void game_over();
};

#endif  // SnakeGame_hpp
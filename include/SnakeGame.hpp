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
        WINNER,        //<! quando o player consegue comer todas as comidas de todos os mapas.
        NEXT_LEVEL     //<! quando o player consegue comer todas as comidas do mapa e pode escolher ir para o próximo nível.
    };

   private:
    Level *m_level;                                  //<! representa o level de mapa atual
    Pacman *m_pacman;                                //<! representa o jogador, que nesse caso sempre será o tipo pacman
    Player m_ia_player;                              //<! instancia da classe Player responsável pela IA do jogo
    GameStates m_state;                              //<! guarda o estado do jogo
    int m_count1 = 0;                                //<! auxilia no operação de colocar comida no mapa, certificando-se que só tenha uma comida no mapa
    int m_count2 = 1;                                //<! contador de mapas concluídos
    int m_frameCount = 0;                            //<! contador de frames, usado apenas como exemplo
    int m_decisao_jogador;                           //<! Representa a escolha do jogador após conseguir todas as comidas.
    int m_action;                                    //<! Representa a ação escolhida pela IA
    int m_nivel = 0;                                 //<! Posição do mapa no vetor com todos os mapas.
    int m_pontos_totais = 0;                         //<! Quantidade de pontos da partida inteira.
    int rodada = 0;
    std::string m_choice;                            //<! usado na função process_actions para guardar a escolha do usuário
    std::string m_levels_file;                       //<! arquivo com os níveis do jogo
    std::string m_modo;                              //<! arquivo com os níveis do jogo
    std::string m_ia;                                //<! arquivo com os níveis do jogo
    std::vector<std::vector<std::string>> m_niveis;  //<! vector com os niveis do jogo.

   public:
    /**
     * @brief Construtor padrão, utiliza os parãmetros inseridos no terminal para utilizar o objeto
     * de diferentes maneiras.
     **/
    SnakeGame(std::string levels, std::string mode, std::string ia);

    /**
     * @brief Chamado no main, este loop executa o jogo indefinidamente até que o usuário escolha terminar!
     */
    void loop();

   private:
    /**
     * @brief Consome o arquivo de mapas para separar e guardar as informações de cada mapa
     * individualmente em um vetor.
     */
    void load_levels();

    /**
     * @brief Retorna um nivel do vector de niveis referente ao índicie mensionado no paramêtro.
     * @param niveis    vector com os niveis do jogo.
     * @param n         número correspondente a algum nivel do vector acima.
     * @return Retorna um nivel.
     */
    std::vector<std::string> get_level(std::vector<std::vector<std::string>> &niveis, int n);

    /**
     * @brief Realiza a inicialização geral do jogo, carregando o primeiro mapa e instanciando o jogador.
     **/
    void initialize_game();

    /**
     * @brief Atualiza o estado do jogo, basicamente movendo os objetos, sorteando novas posições de comida.
     **/
    void update();

    /**
     * @brief Processa as entradas do jogador.
     **/
    void process_actions();

    /**
     * @brief Testa o estado do jogo e desenha a tela correspondente.
     **/
    void render();

    /**
     * @brief É chamada quando o jogo termina a fim de destruir/resetar elementos do estado do jogo.
     **/
    void game_over();
};

#endif  // SnakeGame_hpp
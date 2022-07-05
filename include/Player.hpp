#ifndef Player_hpp
#define Player_hpp

class Player{
    private:
        /*priv*/
    public:
        void find_solution(/*args?*/);
        /**
         * Retorna a próxima ação do jogador um mapeamento de 0-3, representando ir para esquerda, cima, direita, baixo
         * @return a próxima ação do jogador
         **/
        int next_move();
};
#endif //Player_hpp
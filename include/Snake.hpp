#ifndef Snake_hpp
#define Snake_hpp
#include <iostream>

class Snake{

    private:
        int m_posl, m_posc;
        int m_vidas;
        char m_grafico;

    public:
        Snake(int linha_inicial, int coluna_inicial);

        int get_vidas();

        void set_vidas(int vidas);

        std::pair<int, int> get_pos();
        
        void set_pos(std::pair<int,int> pos);
        
        char get_grafico();

        void move(int l, int c);
        
    
};
#endif
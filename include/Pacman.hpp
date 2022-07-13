#ifndef Pacman_hpp
#define Pacman_hpp
#include <iostream>

class Pacman{

    private:
        int m_posl, m_posc;
        int m_vidas;
        char m_grafico;
        int m_qnt_comida = 0;

    public:
        Pacman(int linha_inicial, int coluna_inicial);

        int get_vidas();

        void set_vidas(int vidas);

        std::pair<int, int> get_pos();
        
        void set_pos(std::pair<int,int> pos);
        
        char get_grafico();

        void move(int l, int c);

        std::string mostrar_vidas();

        void set_grafico(char character);
        
        void resetar_qnt_comida();

        void comeu();

        int get_qnt_comida();
};
#endif
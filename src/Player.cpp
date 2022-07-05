#include "Player.hpp"
#include <iostream>

using namespace std;

void Player::find_solution(/*args?*/){
    //"resolve o problema com base no mapa, a posição atual da cobra e a posição atual da comida"
}

int Player::next_move(){
    //sorteia uma ação aleatória que não causa morte
    /*retorna uma ação aleatória entre 0 e 4*/
    return rand()%4;
}
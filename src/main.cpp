#include <iostream>
#include "SnakeGame.hpp"

using namespace std;

int main(int argc, char *argv[]){
    //TODO: processar os argumentos
    SnakeGame game(argv[1], argv[2], argv[3]);
    game.loop(); //bloqueia aqui e só saí quando o jogo termina
    return 0;
}
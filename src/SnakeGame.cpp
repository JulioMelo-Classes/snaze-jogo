#include "SnakeGame.hpp"
#include "Player.hpp"

#include <iostream>
#include <fstream>

#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

using namespace std;

SnakeGame::SnakeGame(string levels){
    m_levels_file=levels;
    m_choice = "";
    m_frameCount = 0;
    initialize_game();
}

void SnakeGame::initialize_game(){
    //carrega o nivel ou os níveis
    ifstream levelFile(m_levels_file); 
    int lineCount = 0;
    string line;
    if(levelFile.is_open()){
        while(getline(levelFile, line)){ //pega cada linha do arquivo
            if(lineCount > 0){ //ignora a primeira linha já que ela contem informações que não são uteis para esse exemplo
                m_maze.push_back(line);
            }
            lineCount++;
        }
    }
    m_state = WAITING_USER; //estado inicial é WAITING_USER, mas poderia ser outro
    m_ia_player = Player();
}



void SnakeGame::process_actions(){
    //processa as entradas do jogador de acordo com o estado do jogo
    //nesse exemplo o jogo tem 3 estados, WAITING_USER, RUNNING e GAME_OVER.
    //no caso deste trabalho temos 2 tipos de entrada, uma que vem da classe Player, como resultado do processamento da IA
    //outra vem do próprio usuário na forma de uma entrada do teclado.
    switch(m_state){
        case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
            cin>>std::ws>>m_choice;
            break;
        case WAITING_IA:
            m_action = m_ia_player.next_move();
            break;
        default:
            //nada pra fazer aqui
            break;
    }
}

void SnakeGame::update(){
    //atualiza o estado do jogo de acordo com o resultado da chamada de "process_input"
    switch(m_state){
        case RUNNING:
            if(m_frameCount>0 && m_frameCount%10 == 0) //depois de 10 frames o jogo pergunta se o usuário quer continuar
                m_state = WAITING_USER;
            break;
        case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
            if(m_choice == "n"){
                m_state = GAME_OVER;
                game_over();
            }
            else{
                //pode fazer alguma coisa antes de fazer isso aqui
                m_state = RUNNING;
            }
            break;
        case WAITING_IA: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
            /*alguma coisa aqui*/
            m_state = RUNNING;
            break;
        default:
            //nada pra fazer aqui
            break;
    }
}

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar
 */
void wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal
 */
void clearScreen(){
//some C++ voodoo here ;D
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

void SnakeGame::render(){
    clearScreen();
    switch(m_state){
        case RUNNING:
            //desenha todas as linhas do labirinto
            for(auto line : m_maze){
                cout<<line<<endl;
            }
            cout<<"fc:"<<m_frameCount<<endl;
            break;
        case WAITING_USER:
            cout<<"Você quer iniciar/continuar o jogo? (s/n)"<<endl;
            break;
        case GAME_OVER:
            cout<<"O jogo terminou!"<<endl;
            break;
    }
    m_frameCount++;
}

void SnakeGame::game_over(){
}

void SnakeGame::loop(){
    render(); //chama um render para a interface inicial
    while(m_state != GAME_OVER){
        process_actions();
        update();
        render();
        wait(1000);// espera 1 segundo entre cada frame
    }
}

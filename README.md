### Sumário
- [🐍 Introdução 🐍](#-introdução-)
  - [Pacman](#pacman)
  - [Snake](#snake)
- [⚙️ Requisitos](#️-requisitos)
    - [Ambiente](#ambiente)
    - [Linguagem de programação](#linguagem-de-programação)
    - [Requisítos de compilação](#requisítos-de-compilação)
  - [Como rodar](#como-rodar)
- [🗺️ Mapas](#️-mapas)
    - [Mapa 1: <br>](#mapa-1-)
    - [Mapa 2: <br>](#mapa-2-)
    - [Mapa 3: <br>](#mapa-3-)
- [🧪 Validações e testes](#-validações-e-testes)
    - [Teste de colisão com mapa](#teste-de-colisão-com-mapa)
    - [Verificação de jogador no mapa](#verificação-de-jogador-no-mapa)
    - [Verificação caso o arquivo não exista](#verificação-caso-o-arquivo-não-exista)
- [🤝 Colaboradores](#-colaboradores)
***
</br>

# 🐍 Introdução 🐍
O programa é uma simulação do jogo da cobrinha, jogo muito famoso nos anos 90 com os celulares da Nokia que vinham com o jogo instalado. Aqui tentamos implementar o jogo da cobrinha e o Pac-Man, porém, com o "jogador" preso em um labirinto e sendo controlada por uma IA.
###

## Pacman
 * Uma das primeiras etapas foi implementar as mecânicas de outro jogo bem famoso, o "Pac-Man". 
  O objetivo da maioria dos jogos da série é percorrer um labirinto, comendo pontos, pontos energizantes e frutas e fugindo de quatro fantasmas, chamados Blinky, Pinky, Inky e Clyde.

<p align="center">
    <img src="https://play-lh.googleusercontent.com/V-lvUzA5kK0Xw3wdg8Ct3vfIMXUX5vXYcNLPmudaZ-eyQjedYz-luqIuLmJO6KodE0Y" width="500">
</p>

## Snake 
 * Uma fina criatura que se arrasta pela tela, coletando comida, não podendo colidir com seu próprio corpo ou com as paredes que estão dentro ou cercando a área de jogo. Cada vez que a serpente come um pedaço de comida, sua cauda cresce, aumentando a dificuldade do jogo.
<p align="center">
    <img src="https://media.istockphoto.com/vectors/classic-retro-snakestyle-game-basic-digital-screen-for-your-design-vector-id1363586427?k=20&m=1363586427&s=612x612&w=0&h=uKW6cbMQCS4ydTzsdIaRiUc1L7Ike-3N0qzBjm-uwis=" width="500">
</p>
</br>

# ⚙️ Requisitos

### Ambiente
  * Linux</br>
      <img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" width="140" height="50"/>

### Linguagem de programação
  * C++</br>
    <img src="https://img.shields.io/badge/-C++%20-00599C?logo=c%2B%2B&style=for-the-badge" width="140" height="50"/>

### Requisítos de compilação
  * CMAKE</br>
    <img src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white" width="140" height="50" alt="CMAKE"/>
  * GCC</br>
    <img src="https://img.shields.io/badge/-GCC %20-A42E2B?logo=gnu&style=for-the-badge" width="140" height="50" alt="GCC"/>
***
## Como rodar
  - ### Tipos de Jogos 
    Há 2 escolhas de tipos de simulação, na flag "-mode" poderá ser escolhido "**snaze**" ou "**pacmaze**". Na flag "-ia" poderá ser escolhido "**random**" ou "**find**".

    O "**pacmaze**" é uma versão mais simples do programa, nele não há uma cobra, mas sim um PacMan.

    A versão com "**find**" é uma forma mais inteligente do pacman/cobra se movimentar, nela é feito a tentativa de achar o caminho mais curto para a comida no mapa.<br>
    (*A implementação da IA "find" não foi implementado, portanto, existe apenas a inteligência "random" para ser jogada.*)

  - ### Para rodar o programa utilize os comandos no terminal na pasta raíz do projeto:
  &emsp; &emsp; 👇
  1. ```
      mkdir build
     ```
  2. ```
      cd build
     ```
  3. ```
      cmake ..
     ```
  4. ```
      cmake --build .
     ```
  5. ```
      ./snaze ../data/mazes.txt -mode pacmaze -ia random    
     ```
  &emsp; &emsp; 👆


   

</br>

</br>

# 🗺️ Mapas
 - O "v" aponta a posição inicia do jogador no mapa. <br>
 - Cada mapa tem uma quantidade de comidas diferentes.
### Mapa 1: <br>
<img src="https://user-images.githubusercontent.com/71523376/179438513-8409cd51-b262-46b6-8eeb-e6c88be26291.png" width="15%">

### Mapa 2: <br>
<img src="https://user-images.githubusercontent.com/71523376/179438542-7e07cea6-fab9-4b61-8d5c-3b6b445a8400.png" width="15%">

### Mapa 3: <br>
<img src="https://user-images.githubusercontent.com/71523376/179438563-f9fe6dfb-9997-4361-9277-6c019a55d416.png" width="30%">

</br>

# 🧪 Validações e testes
<i>Utilize os comandos abaixo no terminal.</i>


### Teste de colisão com mapa
`Simulação de mapa onde o jogador está preso e inevitavelmente irá colidir em alguma direção.`
  - ```
    ./snaze ../data/testes/colisao.txt -mode pacmaze -ia random
    ```
  - `O player irá colidir com as paredes até que acabem suas vidas.`

<img src="https://user-images.githubusercontent.com/71523376/179371880-118e02c3-1c0c-4595-b81c-33644349864a.png" width="150px">

</br>

### Verificação de jogador no mapa
  - ```
    ./snaze ../data/testes/jogadorInexistente.txt  -mode pacmaze -ia random
    ```
  - Saída esperada **`Erro! Não foi encontrado nenhum ponto inicial do player no mapa 2.`**
### Verificação caso o arquivo não exista
  - ```
    ./snaze ../data/testes/inexistente.txt -mode pacmaze -ia random
    ```
  - Saída esperada **`Erro! Arquivo inexistente.`**

</br>

# 🤝 Colaboradores
  * [Danrley Lima](https://github.com/Danrley-Lima)
  * [Lucas Morais](https://github.com/lucas-morais27)
  
***

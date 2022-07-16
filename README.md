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
  - [🚧🚧 EM DESENVOLVIMENTO 🚧🚧](#-em-desenvolvimento-)
- [🧪 Validações e testes](#-validações-e-testes)
  - [🚧🚧 EM DESENVOLVIMENTO 🚧🚧](#-em-desenvolvimento--1)
    - [Verificação de caracteres especiais](#verificação-de-caracteres-especiais)
    - [Verificação de peso negativo](#verificação-de-peso-negativo)
    - [Verificação de palavra vazia](#verificação-de-palavra-vazia)
    - [Verificação de peso vazio](#verificação-de-peso-vazio)
    - [Verificação caso o arquivo não exista](#verificação-caso-o-arquivo-não-exista)
- [🤝 Colaboradores](#-colaboradores)
- [🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧](#)
***
</br>

# 🐍 Introdução 🐍
O programa é uma simulação do jogo da cobrinha, jogo muito famoso nos anos 90 com os celulares da Nokia que vinham com o jogo instalado. Aqui tentamos implementar o jogo da cobrinha, porém, com a cobra presa em um labirinto e sendo controlada por uma IA.
###

## Pacman
 * Uma das primeiras etapas foi implementar as mecânicas de outro jogo bem famoso, o "Pac-Man". 

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
    Há 2 escolhas de tipos de simulação, na flag "-mode" poderá ser escolhido "snaze" ou "pacmaze". Na flag "-ia" poderá ser escolhido "random" ou "find".

    O "**pacmaze**" é uma versão mais simples do programa, nele não há uma cobra, mas sim um PacMan.

    A versão com "**find**" é uma forma mais inteligente do pacman/cobra se movimentar, nela é feito a tentativa de achar o caminho mais curto para a comida no mapa.

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
      ./snaze ../data/maze2.txt -mode pacmaze -ia random    
     ```
  &emsp; &emsp; 👆


   

</br>

</br>

# 🗺️ Mapas
## 🚧🚧 EM DESENVOLVIMENTO 🚧🚧

</br>

# 🧪 Validações e testes
Testes para verificar se a base de dados está em conformidade para ser utilizada pelo programa.</br>
<i>Utilize os comandos abaixo no terminal.</i>

## 🚧🚧 EM DESENVOLVIMENTO 🚧🚧
### Verificação de caracteres especiais
  - ```
    ./words_complete_correct ../data/testes/teste_caractere.txt
    ```
  - Saída esperada **`Erro! Caractere inválido & na linha 2.`**

</br>

### Verificação de peso negativo
  - ```
    ./words_complete_correct ../data/testes/teste_negativo.txt
    ```
  - Saída esperada **`Erro! Peso negativo na linha 3.`**

</br>

### Verificação de palavra vazia
  - ```
    ./words_complete_correct ../data/testes/teste_vazio.txt
    ```
  - Saída esperada **`Erro! Palavra vazia na linha 4.`**

</br>

### Verificação de peso vazio
  - ```
    ./words_complete_correct ../data/testes/teste_peso_vazio.txt
    ```
  - Saída esperada **`Erro! Peso vazio na linha 3.`**

</br>

### Verificação caso o arquivo não exista
  - ```
    ./words_complete_correct ../data/testes/teste_inexistente.txt
    ```
  - Saída esperada **`Erro! Arquivo inexistente.`**

</br>

# 🤝 Colaboradores
  * [Danrley Lima](https://github.com/Danrley-Lima)
  * [Lucas Morais](https://github.com/lucas-morais27)
  
***
# 🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧🚧

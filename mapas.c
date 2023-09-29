#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdbool.h>
#include "chefao.c"
#include "funcoes_auxiliares.h"
#include "c_personagem.h"

void mapa_1_1(struct Personagem personagem) {
  int i, j;
  printf("Encontre o chefão!");
  // Definir o mapa
  char map[20][20] = {
    "11111111111111111111",
    "00000200000000000051",
    "10101110111110011111",
    "10000000000000000001",
    "10111000100010001001",
    "10100000000000200001",
    "10111011131110011101",
    "15100000000000100011",
    "10001111100011111041",
    "10000000001000000011",
    "10111000110211101111",
    "10100010001000130001",
    "10001000100010001001",
    "14000210001000100511",
    "10011111111110111111",
    "10003110011110200001",
    "10000000110010001041",
    "10111110011000001001",
    "10000011100011011071",
    "11111111111111111111"
  };

  // Posição inicial do elemento "x"
  int x = 0;
  int y = 1;

  // Variável para controlar a duração do campo de visão expandido
  int turno_mais_visao = 0;

  

  // Loop do jogo
  while (1) {
    int ver_armadilha;
      if(personagem.profissao == 3){
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 12.0) * 100;
      } else {
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 20.0) * 100;
      }
    int random_number = rand() % 100;  // Gera um número aleatório de 0 a 99
    // Imprimir o mapa com a posição atual do elemento "x" e as áreas visíveis
    for (i = 0; i < 20; i++) {
      for (j = 0; j < 20; j++) {
        if (map[i][j] == '0') {
          map[i][j] = ' ';
        }
        if (map[i][j] == '2') {
          map[i][j] = 'T';
        }
        if (map[i][j] == '3') {
          map[i][j] = 'H';
        }
        if (map[i][j] == '4') {
          map[i][j] = 'A';
        }
        if (map[i][j] == '5') {
          map[i][j] = 'V';
        }
        if (map[i][j] == '7'){
          map[i][j] = 'C';
        }
        else if (i == y && j == x) {
          printf("x");
        }
        else if (map[i][j] == '2' && i == y && j == x) {
            printf("%c", map[i][j]);
        }
        else if (map[i][j] == '3' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '4' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '5' && i == y && j == x) {
          printf("%c", map[i][j]);
        }
        else if (turno_mais_visao > 0 && abs(i - y) <= 4 && abs(j - x) <= 4) {
          printf("%c", map[i][j]);
        }
        else if (abs(i - y) <= 2 && abs(j - x) <= 2) {
          printf("%c", map[i][j]);
        } 
        else {
          printf("?");
        }
      }
      printf("\n");
    }
    
    // Status do Personagem e Legenda:
    printf("Vida atual: %d\n", personagem.vida_personagem);
    printf("Legenda:\n");
    printf("T = armadilha;\n");
    printf("H = +vida;\n");
    printf("A = +atributos;\n");
    printf("V = +visão;\n");
    printf("C = chefão.\n");

    // Ler a entrada do jogador
    int input;

    input = le_tecla();
    system("clear");

    // Atualizar a posição do elemento "x" com base na entrada do jogador
    int newX = x;
    int newY = y;

    if(input == 'a' && x > 0 && map[y][x - 1] != '1') {
      newX = x - 1;  // Mover para a esquerda
    }
    else if(input == 'd' && x < 19 && map[y][x + 1] != '1') {
      newX = x + 1;  // Mover para a direita
    }
    else if(input == 'w' && y > 0 && map[y - 1][x] != '1') {
      newY = y - 1;  // Mover para cima
    }
    else if(input == 's' && y < 19 && map[y + 1][x] != '1') {
      newY = y + 1;  // Mover para baixo
    }


      // Atualizar a posição do elemento "x" se for diferente da posição atual
    if (newX != x || newY != y) {
    x = newX;
    y = newY;

      if(map[y][x] == 'T'){
        personagem.vida_personagem -= 5;
        map[y][x] = ' '; // Alterar '2' para espaço em branco
      }
      else if (map[y][x] == 'H'){
        personagem.vida_personagem += 2;
        map[y][x] = ' ';  // Alterar '3' para espaço em branco
      }
      else if (personagem.profissao == 1 && map[y][x] == 'A') {
        personagem.forca += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 2 && map[y][x] == 'A') {
        personagem.inteligencia += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 3 && map[y][x] == 'A') {
        personagem.destreza += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (map[y][x] == 'V') {
        turno_mais_visao = 10;  // Definir o tempo de duração do campo de visão expandido em segundos
        map[y][x] = ' ';  // Alterar '5' para espaço em branco
      }
      else if (map[y][x] == 'C'){
        chefao(personagem);
        break;
      }
    }

    // Reduzir o tempo de duração do campo de visão expandido a cada iteração
    if (turno_mais_visao > 0) {
       turno_mais_visao--;
    }
    if (personagem.vida_personagem <= 0) {  //  Caso a vida chegue a 0, o jogo acaba
      printf("\n\nGAME OVER !\n");
      break;  // Encerrar o jogo
    }
  }
}

void mapa_1_2(struct Personagem personagem) {
  int i, j;
  // Definir o mapa
  char map[20][20] = {
    "11111111111111111111",
    "00000000000000000001",
    "11101110111110011111",
    "10000010200015000001",
    "10001011100010001111",
    "10100000000000000001",
    "14111110101110111111",
    "11150000000100130001",
    "10001000100120102111",
    "10000000111000100011",
    "10111000111011101111",
    "10102010001000150001",
    "10001000131110001101",
    "10000010001011100111",
    "10011110111000101111",
    "13010010201111000041",
    "10011000100001001111",
    "11000010101100001001",
    "10010011104111000071",
    "11111111111111111111"
  };
    
  // Posição inicial do elemento "x"
  int x = 0;
  int y = 1;

  // Variável para controlar a duração do campo de visão expandido
  int turno_mais_visao = 0;

  

  // Loop do jogo
  while (1) {
    int ver_armadilha;
      if(personagem.profissao == 3){
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 12.0) * 100;
      } else {
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 20.0) * 100;
      }
    int random_number = rand() % 100;  // Gera um número aleatório de 0 a 99
    // Imprimir o mapa com a posição atual do elemento "x" e as áreas visíveis
    for (i = 0; i < 20; i++) {
      for (j = 0; j < 20; j++) {
        if (map[i][j] == '0') {
          map[i][j] = ' ';
        }
        if (map[i][j] == '2') {
          map[i][j] = 'T';
        }
        if (map[i][j] == '3') {
          map[i][j] = 'H';
        }
        if (map[i][j] == '4') {
          map[i][j] = 'A';
        }
        if (map[i][j] == '5') {
          map[i][j] = 'V';
        }
        if (map[i][j] == '7'){
          map[i][j] = 'C';
        }
        else if (i == y && j == x) {
          printf("x");
        }
        else if (map[i][j] == '2' && i == y && j == x) {
            printf("%c", map[i][j]);
        }
        else if (map[i][j] == '3' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '4' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '5' && i == y && j == x) {
          printf("%c", map[i][j]);
        }
        else if (turno_mais_visao > 0 && abs(i - y) <= 4 && abs(j - x) <= 4) {
          printf("%c", map[i][j]);
        }
        else if (abs(i - y) <= 2 && abs(j - x) <= 2) {
          printf("%c", map[i][j]);
        } 
        else {
          printf("?");
        }
      }
      printf("\n");
    }
    
    // Status do Personagem e Legenda:
    printf("Vida atual: %d\n", personagem.vida_personagem);
    printf("Legenda:\n");
    printf("T = armadilha;\n");
    printf("H = +vida;\n");
    printf("A = +atributos;\n");
    printf("V = +visão;\n");
    printf("C = chefão.\n");

    // Ler a entrada do jogador
    int input;

    input = le_tecla();
    system("clear");

    // Atualizar a posição do elemento "x" com base na entrada do jogador
    int newX = x;
    int newY = y;

    if(input == 'a' && x > 0 && map[y][x - 1] != '1') {
      newX = x - 1;  // Mover para a esquerda
    }
    else if(input == 'd' && x < 19 && map[y][x + 1] != '1') {
      newX = x + 1;  // Mover para a direita
    }
    else if(input == 'w' && y > 0 && map[y - 1][x] != '1') {
      newY = y - 1;  // Mover para cima
    }
    else if(input == 's' && y < 19 && map[y + 1][x] != '1') {
      newY = y + 1;  // Mover para baixo
    }


      // Atualizar a posição do elemento "x" se for diferente da posição atual
    if (newX != x || newY != y) {
    x = newX;
    y = newY;

      if(map[y][x] == 'T'){
        personagem.vida_personagem -= 5;
        map[y][x] = ' '; // Alterar '2' para espaço em branco
      }
      else if (map[y][x] == 'H'){
        personagem.vida_personagem += 2;
        map[y][x] = ' ';  // Alterar '3' para espaço em branco
      }
      else if (personagem.profissao == 1 && map[y][x] == 'A') {
        personagem.forca += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 2 && map[y][x] == 'A') {
        personagem.inteligencia += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 3 && map[y][x] == 'A') {
        personagem.destreza += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (map[y][x] == 'V') {
        turno_mais_visao = 10;  // Definir o tempo de duração do campo de visão expandido em segundos
        map[y][x] = ' ';  // Alterar '5' para espaço em branco
      }
      else if (map[y][x] == 'C'){
        chefao(personagem);
        break;
      }
    }

    // Reduzir o tempo de duração do campo de visão expandido a cada iteração
    if (turno_mais_visao > 0) {
       turno_mais_visao--;
    }
    if (personagem.vida_personagem <= 0) {  //  Caso a vida chegue a 0, o jogo acaba
      printf("\n\nGAME OVER !\n");
      break;  // Encerrar o jogo
    }
  }
}

void mapa_2_1(struct Personagem personagem) {
  int i, j;
  // Definir o mapa
  char map[30][30] = {
    "111111111111111111111111111111",
    "000000001000101000001000001051",
    "111110111010101011101111101101",
    "100002000010100013100000000011",
    "101111111010101010101011101011",
    "100014000010001010102000001011",
    "101110111110111110101010111111",
    "100010000010100000131010001041",
    "111011111010111110111111111011",
    "101010001010001000100005100011",
    "101110101011111011111011111011",
    "150000100010000020001000001011",
    "111110111111111111101011101111",
    "100000000000140000001000101001",
    "111111111110111111101010111111",
    "130000001000000000100010001011",
    "111011111010101011111110111011",
    "100000001010100010000010051011",
    "101111101010111110101111111011",
    "141000001000000010100000201001",
    "111010111111101110101110111111",
    "100010200010001000101000001011",
    "101110111010111011111011101011",
    "101000100000100000001310101011",
    "101011111010101010101110101111",
    "131510101010001000100410000011",
    "111110101111111111111010101011",
    "100000001020001000001020100011",
    "170000000011100010100000000001",
    "111111111111111111111111111111"
  };

  // Posição inicial do elemento "x"
  int x = 0;
  int y = 1;

  // Variável para controlar a duração do campo de visão expandido
  int turno_mais_visao = 0;

  

  // Loop do jogo
  while (1) {
    int ver_armadilha;
      if(personagem.profissao == 3){
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 12.0) * 100;
      } else {
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 20.0) * 100;
      }
    int random_number = rand() % 100;  // Gera um número aleatório de 0 a 99
    // Imprimir o mapa com a posição atual do elemento "x" e as áreas visíveis
    for (i = 0; i < 30; i++) {
      for (j = 0; j < 30; j++) {
        if (map[i][j] == '0') {
          map[i][j] = ' ';
        }
        if (map[i][j] == '2') {
          map[i][j] = 'T';
        }
        if (map[i][j] == '3') {
          map[i][j] = 'H';
        }
        if (map[i][j] == '4') {
          map[i][j] = 'A';
        }
        if (map[i][j] == '5') {
          map[i][j] = 'V';
        }
        if (map[i][j] == '7'){
          map[i][j] = 'C';
        }
        else if (i == y && j == x) {
          printf("x");
        }
        else if (map[i][j] == '2' && i == y && j == x) {
            printf("%c", map[i][j]);
        }
        else if (map[i][j] == '3' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '4' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '5' && i == y && j == x) {
          printf("%c", map[i][j]);
        }
        else if (turno_mais_visao > 0 && abs(i - y) <= 4 && abs(j - x) <= 4) {
          printf("%c", map[i][j]);
        }
        else if (abs(i - y) <= 2 && abs(j - x) <= 2) {
          printf("%c", map[i][j]);
        } 
        else {
          printf("?");
        }
      }
      printf("\n");
    }
    
    // Status do Personagem e Legenda:
    printf("Vida atual: %d\n", personagem.vida_personagem);
    printf("Legenda:\n");
    printf("T = armadilha;\n");
    printf("H = +vida;\n");
    printf("A = +atributos;\n");
    printf("V = +visão;\n");
    printf("C = chefão.\n");

    // Ler a entrada do jogador
    int input;

    input = le_tecla();
    system("clear");

    // Atualizar a posição do elemento "x" com base na entrada do jogador
    int newX = x;
    int newY = y;

    if(input == 'a' && x > 0 && map[y][x - 1] != '1') {
      newX = x - 1;  // Mover para a esquerda
    }
    else if(input == 'd' && x < 29 && map[y][x + 1] != '1') {
      newX = x + 1;  // Mover para a direita
    }
    else if(input == 'w' && y > 0 && map[y - 1][x] != '1') {
      newY = y - 1;  // Mover para cima
    }
    else if(input == 's' && y < 29 && map[y + 1][x] != '1') {
      newY = y + 1;  // Mover para baixo
    }


      // Atualizar a posição do elemento "x" se for diferente da posição atual
    if (newX != x || newY != y) {
    x = newX;
    y = newY;

      if(map[y][x] == 'T'){
        personagem.vida_personagem -= 5;
        map[y][x] = ' '; // Alterar '2' para espaço em branco
      }
      else if (map[y][x] == 'H'){
        personagem.vida_personagem += 2;
        map[y][x] = ' ';  // Alterar '3' para espaço em branco
      }
      else if (personagem.profissao == 1 && map[y][x] == 'A') {
        personagem.forca += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 2 && map[y][x] == 'A') {
        personagem.inteligencia += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 3 && map[y][x] == 'A') {
        personagem.destreza += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (map[y][x] == 'V') {
        turno_mais_visao = 15;  // Definir o tempo de duração do campo de visão expandido em segundos
        map[y][x] = ' ';  // Alterar '5' para espaço em branco
      }
      else if (map[y][x] == 'C'){
        chefao(personagem);
        break;
      }
    }

    // Reduzir o tempo de duração do campo de visão expandido a cada iteração
    if (turno_mais_visao > 0) {
       turno_mais_visao--;
    }
    if (personagem.vida_personagem <= 0) {  //  Caso a vida chegue a 0, o jogo acaba
      printf("\n\nGAME OVER !\n");
      break;  // Encerrar o jogo
    }
  }
}

void mapa_2_2(struct Personagem personagem) {
  int i, j;
  // Definir o mapa
  char map[30][30] = {
    "111111111111111111111111111111",
    "000010001000000010101000001311",
    "111011101111111010101110111011",
    "100000001500000010000000001011",
    "101010111110101011101110101011",
    "101010021000101010000000100511",
    "111110111011111010111010111111",
    "100000000000001000001010200011",
    "141111111113111011111011141111",
    "100000100020001010001000101011",
    "111110101111101110111010111011",
    "100000100010000010001010100011",
    "101110111011101110111011111011",
    "151000000000101000001000001011",
    "111011111010111111111311111111",
    "140010201010000000100000000051",
    "101111111011111110111111111011",
    "100000001010000010001010201011",
    "111111111111111011101010101011",
    "130010100000150010000000100001",
    "101110101010111111101011111111",
    "100010001012000000001000001011",
    "111111111111111011111111101011",
    "100010000000000014001000200011",
    "111010111111111111101011101111",
    "100000100000000010000010001001",
    "111110101111101113111111101111",
    "141000101000001000000000100001",
    "100000101111111111111110100071",
    "111111111111111111111111111111"
  };

  // Posição inicial do elemento "x"
  int x = 0;
  int y = 1;

  // Variável para controlar a duração do campo de visão expandido
  int turno_mais_visao = 0;

  

  // Loop do jogo
  while (1) {
    int ver_armadilha;
      if(personagem.profissao == 3){
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 12.0) * 100;
      } else {
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 20.0) * 100;
      }
    int random_number = rand() % 100;  // Gera um número aleatório de 0 a 99
    // Imprimir o mapa com a posição atual do elemento "x" e as áreas visíveis
    for (i = 0; i < 30; i++) {
      for (j = 0; j < 30; j++) {
        if (map[i][j] == '0') {
          map[i][j] = ' ';
        }
        if (map[i][j] == '2') {
          map[i][j] = 'T';
        }
        if (map[i][j] == '3') {
          map[i][j] = 'H';
        }
        if (map[i][j] == '4') {
          map[i][j] = 'A';
        }
        if (map[i][j] == '5') {
          map[i][j] = 'V';
        }
        if (map[i][j] == '7'){
          map[i][j] = 'C';
        }
        else if (i == y && j == x) {
          printf("x");
        }
        else if (map[i][j] == '2' && i == y && j == x) {
            printf("%c", map[i][j]);
        }
        else if (map[i][j] == '3' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '4' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '5' && i == y && j == x) {
          printf("%c", map[i][j]);
        }
        else if (turno_mais_visao > 0 && abs(i - y) <= 4 && abs(j - x) <= 4) {
          printf("%c", map[i][j]);
        }
        else if (abs(i - y) <= 2 && abs(j - x) <= 2) {
          printf("%c", map[i][j]);
        } 
        else {
          printf("?");
        }
      }
      printf("\n");
    }
    
    // Status do Personagem e Legenda:
    printf("Vida atual: %d\n", personagem.vida_personagem);
    printf("Legenda:\n");
    printf("T = armadilha;\n");
    printf("H = +vida;\n");
    printf("A = +atributos;\n");
    printf("V = +visão;\n");
    printf("C = chefão.\n");

    // Ler a entrada do jogador
    int input;

    input = le_tecla();
    system("clear");

    // Atualizar a posição do elemento "x" com base na entrada do jogador
    int newX = x;
    int newY = y;

    if(input == 'a' && x > 0 && map[y][x - 1] != '1') {
      newX = x - 1;  // Mover para a esquerda
    }
    else if(input == 'd' && x < 29 && map[y][x + 1] != '1') {
      newX = x + 1;  // Mover para a direita
    }
    else if(input == 'w' && y > 0 && map[y - 1][x] != '1') {
      newY = y - 1;  // Mover para cima
    }
    else if(input == 's' && y < 29 && map[y + 1][x] != '1') {
      newY = y + 1;  // Mover para baixo
    }


      // Atualizar a posição do elemento "x" se for diferente da posição atual
    if (newX != x || newY != y) {
    x = newX;
    y = newY;

      if(map[y][x] == 'T'){
        personagem.vida_personagem -= 5;
        map[y][x] = ' '; // Alterar '2' para espaço em branco
      }
      else if (map[y][x] == 'H'){
        personagem.vida_personagem += 2;
        map[y][x] = ' ';  // Alterar '3' para espaço em branco
      }
      else if (personagem.profissao == 1 && map[y][x] == 'A') {
        personagem.forca += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 2 && map[y][x] == 'A') {
        personagem.inteligencia += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 3 && map[y][x] == 'A') {
        personagem.destreza += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (map[y][x] == 'V') {
        turno_mais_visao = 15;  // Definir o tempo de duração do campo de visão expandido em segundos
        map[y][x] = ' ';  // Alterar '5' para espaço em branco
      }
      else if (map[y][x] == 'C'){
        chefao(personagem);
        break;
      }
    }

    // Reduzir o tempo de duração do campo de visão expandido a cada iteração
    if (turno_mais_visao > 0) {
       turno_mais_visao--;
    }
    if (personagem.vida_personagem <= 0) {  //  Caso a vida chegue a 0, o jogo acaba
      printf("\n\nGAME OVER !\n");
      break;  // Encerrar o jogo
    }
  }
}

void mapa_3_1(struct Personagem personagem) {
  int i, j;
  // Definir o mapa
  char map[50][50] = {
    "11111111111111111111111111111111111111111111111111",
    "00000000100000100000001000000000100010000000000001",
    "11111110151111101011101111111010111010111011111101",
    "10000000000000001000000000000010000000001000001001",
    "10111010141011111010111010111110111011101111111001",
    "10000000000010001010100020000010001000100000000001",
    "11111011111111111110111010111111101114101111111111",
    "10001000100000000010100015000000100000101000101011",
    "10111110111110111010101011111011111010101111101011",
    "10001000000000101000001000001010000010021000000011",
    "10111011101111101111101111101010101110111110111111",
    "10000010051000001010101000100010101000000000000001",
    "11111110101210111010111010111110101111111411111101",
    "10000000000000000000001000000000101010001000001001",
    "10111111111111111010111111111010111011101111111111",
    "10001010000004100010000000000200000000151000100011",
    "10111011111111101111111010111111111011101011111011",
    "10100000001000101010100010000010001000101000000011",
    "10111110111110111010101110111110101010101111101111",
    "10100010002000101010101000001000101010200000001011",
    "11101111101115101111111110111110111011101011100011",
    "10001010001000001010101010100000041010001010000011",
    "10111011101110111010101010111110111010111111111111",
    "10000000101010100010100000000200100010100000000011",
    "11101111101010101110111111101111101110111011111011",
    "10001002000010101000101010000000001010101000100011",
    "11111110101410101011101010101011101011101011111111",
    "10100015101010001000000000101000101010100010001001",
    "10111011111110101111111011111110111010101011111111",
    "10100010000010101000100015000000101010101000000011",
    "11111110101111111110101010111111101010111111111511",
    "10001000100010001000001000100010101002001000001011",
    "11101011111111111010111111111010111111111111101111",
    "10001010100002001014000010000010001000000010000011",
    "11111110111010111010101110111011101110111011111011",
    "10000010000010100000100000100010001000001000101011",
    "11101011111111111011101110111011111111111110101011",
    "10001000001000000010000000201010001000001000100011",
    "10111411101511111011111111101010111111111411111111",
    "10100010001010000000100010000010101000101000100011",
    "10111110111011111110101011111111101010101111101011",
    "10100010020010000000101010101010000025100000001001",
    "10101011111011101110101110101010111111111110111001",
    "10001000001010000010001000000000100000001000001001",
    "11111110101110111111141010101111111010111110111111",
    "10001000101000100010000010100010000010001010000011",
    "10111011111111101011101111101111111011111011101111",
    "10002010101000001000100000100020000000001010000011",
    "10100010101000001110100000111100000011100711101111",
    "11111111111111111111111111111111111111111111111111"
  };
    
  // Posição inicial do elemento "x"
  int x = 0;
  int y = 1;

  // Variável para controlar a duração do campo de visão expandido
  int turno_mais_visao = 0;

  

  // Loop do jogo
  while (1) {
    int ver_armadilha;
      if(personagem.profissao == 3){
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 12.0) * 100;
      } else {
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 20.0) * 100;
      }
    int random_number = rand() % 100;  // Gera um número aleatório de 0 a 99
    // Imprimir o mapa com a posição atual do elemento "x" e as áreas visíveis
    for (i = 0; i < 50; i++) {
      for (j = 0; j < 50; j++) {
        if (map[i][j] == '0') {
          map[i][j] = ' ';
        }
        if (map[i][j] == '2') {
          map[i][j] = 'T';
        }
        if (map[i][j] == '3') {
          map[i][j] = 'H';
        }
        if (map[i][j] == '4') {
          map[i][j] = 'A';
        }
        if (map[i][j] == '5') {
          map[i][j] = 'V';
        }
        if (map[i][j] == '7'){
          map[i][j] = 'C';
        }
        else if (i == y && j == x) {
          printf("x");
        }
        else if (map[i][j] == '2' && i == y && j == x) {
            printf("%c", map[i][j]);
        }
        else if (map[i][j] == '3' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '4' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '5' && i == y && j == x) {
          printf("%c", map[i][j]);
        }
        else if (turno_mais_visao > 0 && abs(i - y) <= 4 && abs(j - x) <= 4) {
          printf("%c", map[i][j]);
        }
        else if (abs(i - y) <= 2 && abs(j - x) <= 2) {
          printf("%c", map[i][j]);
        } 
        else {
          printf("?");
        }
      }
      printf("\n");
    }
    
    // Status do Personagem e Legenda:
    printf("Vida atual: %d\n", personagem.vida_personagem);
    printf("Legenda:\n");
    printf("T = armadilha;\n");
    printf("H = +vida;\n");
    printf("A = +atributos;\n");
    printf("V = +visão;\n");
    printf("C = chefão.\n");

    // Ler a entrada do jogador
    int input;

    input = le_tecla();
    system("clear");

    // Atualizar a posição do elemento "x" com base na entrada do jogador
    int newX = x;
    int newY = y;

    if(input == 'a' && x > 0 && map[y][x - 1] != '1') {
      newX = x - 1;  // Mover para a esquerda
    }
    else if(input == 'd' && x < 49 && map[y][x + 1] != '1') {
      newX = x + 1;  // Mover para a direita
    }
    else if(input == 'w' && y > 0 && map[y - 1][x] != '1') {
      newY = y - 1;  // Mover para cima
    }
    else if(input == 's' && y < 49 && map[y + 1][x] != '1') {
      newY = y + 1;  // Mover para baixo
    }


      // Atualizar a posição do elemento "x" se for diferente da posição atual
    if (newX != x || newY != y) {
    x = newX;
    y = newY;

      if(map[y][x] == 'T'){
        personagem.vida_personagem -= 5;
        map[y][x] = ' '; // Alterar '2' para espaço em branco
      }
      else if (map[y][x] == 'H'){
        personagem.vida_personagem += 2;
        map[y][x] = ' ';  // Alterar '3' para espaço em branco
      }
      else if (personagem.profissao == 1 && map[y][x] == 'A') {
        personagem.forca += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 2 && map[y][x] == 'A') {
        personagem.inteligencia += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 3 && map[y][x] == 'A') {
        personagem.destreza += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (map[y][x] == 'V') {
        turno_mais_visao = 17;  // Definir o tempo de duração do campo de visão expandido em segundos
        map[y][x] = ' ';  // Alterar '5' para espaço em branco
      }
      else if (map[y][x] == 'C'){
        chefao(personagem);
        break;
      }
    }

    // Reduzir o tempo de duração do campo de visão expandido a cada iteração
    if (turno_mais_visao > 0) {
       turno_mais_visao--;
    }
    if (personagem.vida_personagem <= 0) {  //  Caso a vida chegue a 0, o jogo acaba
      printf("\n\nGAME OVER !\n");
      break;  // Encerrar o jogo
    }
  }
}

void mapa_3_2(struct Personagem personagem) {
  int i, j;
  // Definir o mapa
  char map[50][50] = {
    "11111111111111111111111111111111111111111111111111",
    "00000000100000100010000000100010000010000010000001",
    "11111110101111101011101111111010111010111011111101",
    "10100010101000001000100010000200100015000000000001",
    "10111010101011111010111010111110111011101111111011",
    "10004000000015001010000000000010000000001000000011",
    "11111011111111111110111010111111101110101110111111",
    "10001000100000000010101010001000100014101000001011",
    "10111110111110111010101011111011111010101111101011",
    "10001000101200101000101010001010001010021000000011",
    "10111011101111101111141111101010101110111110111111",
    "10001010001000101010101000100010101000150000000001",
    "11111110101010111010111010111110101111111011111101",
    "10001000001000000000001000100010101010001000001001",
    "11111111111111111010111111111010111011101111111011",
    "10001010000005100010100010000010100020101000100001",
    "10111011111111101111111010111111111011101011111001",
    "10100000001000101010100010000010001000101000100001",
    "10111110111110111210101110111110101010101111101111",
    "10100014000000101010101000001000101010000010001011",
    "11101111101110101111111110111110111011101011101011",
    "1000101000100000101010101010000051010000000000011",
    "10111011101110111010101010111110111010111111111111",
    "10000200101010100010100000000000101010100002000041",
    "11101111101010101110111111101111101110111011111011",
    "10051000000010101000101010101010001010001000100001",
    "11111110101010101011101010101011101011101011111111",
    "10100010101010001000001000101200101010100010001001",
    "10111011111110101111111011111110111010101011111111",
    "10100014000010000000100010000000001010101000000001",
    "11111110101111111110101010111111101010111111111001",
    "10001000120010000000501000000010001000021500000001",
    "11101011111111111010111111111010111111111111141111",
    "10001010100000000010102010001010001000000010000001",
    "11111110111010111010101110111011101110111011111001",
    "10001000000010100010100010100000000000001000000001",
    "11101011111111111011101110111011111111111110101001",
    "10100000001000100010001000101010001000001000100001",
    "10111011101011111011111111101010111111111011111111",
    "10000210151000000004100010000210101000101000101011",
    "10111110111011111110101011111111101010101111101011",
    "10100010100010000000101010101010000000100000100001",
    "10101011111011101110101110101010111111111110111111",
    "10101000001010000010001010000000100002001000001001",
    "11111110001110111111101010101111111010111110111101",
    "10000000140000102010000010100010000014001010000071",
    "10111111111111101011100011101111111011111511101111",
    "10100010100000001000100000100000001000001010000011",
    "10000010001110001000111111100000001000001011101111",
    "11111111111111111111111111111111111111111111111111"
  };
    
  // Posição inicial do elemento "x"
  int x = 0;
  int y = 1;

  // Variável para controlar a duração do campo de visão expandido
  int turno_mais_visao = 0;

  

  // Loop do jogo
  while (1) {
    int ver_armadilha;
      if(personagem.profissao == 3){
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 12.0) * 100;
      } else {
        ver_armadilha = ((personagem.destreza + personagem.inteligencia) / 20.0) * 100;
      }
    int random_number = rand() % 100;  // Gera um número aleatório de 0 a 99
    // Imprimir o mapa com a posição atual do elemento "x" e as áreas visíveis
    for (i = 0; i < 50; i++) {
      for (j = 0; j < 50; j++) {
        if (map[i][j] == '0') {
          map[i][j] = ' ';
        }
        if (map[i][j] == '2') {
          map[i][j] = 'T';
        }
        if (map[i][j] == '3') {
          map[i][j] = 'H';
        }
        if (map[i][j] == '4') {
          map[i][j] = 'A';
        }
        if (map[i][j] == '5') {
          map[i][j] = 'V';
        }
        if (map[i][j] == '7'){
          map[i][j] = 'C';
        }
        else if (i == y && j == x) {
          printf("x");
        }
        else if (map[i][j] == '2' && i == y && j == x) {
            printf("%c", map[i][j]);
        }
        else if (map[i][j] == '3' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '4' && i == y && j == x){
          printf("%c", map[i][j]);
        }
        else if (map[i][j] == '5' && i == y && j == x) {
          printf("%c", map[i][j]);
        }
        else if (turno_mais_visao > 0 && abs(i - y) <= 4 && abs(j - x) <= 4) {
          printf("%c", map[i][j]);
        }
        else if (abs(i - y) <= 2 && abs(j - x) <= 2) {
          printf("%c", map[i][j]);
        } 
        else {
          printf("?");
        }
      }
      printf("\n");
    }
    
    // Status do Personagem e Legenda:
    printf("Vida atual: %d\n", personagem.vida_personagem);
    printf("Legenda:\n");
    printf("T = armadilha;\n");
    printf("H = +vida;\n");
    printf("A = +atributos;\n");
    printf("V = +visão;\n");
    printf("C = chefão.\n");

    // Ler a entrada do jogador
    int input;

    input = le_tecla();
    system("clear");

    // Atualizar a posição do elemento "x" com base na entrada do jogador
    int newX = x;
    int newY = y;

    if(input == 'a' && x > 0 && map[y][x - 1] != '1') {
      newX = x - 1;  // Mover para a esquerda
    }
    else if(input == 'd' && x < 49 && map[y][x + 1] != '1') {
      newX = x + 1;  // Mover para a direita
    }
    else if(input == 'w' && y > 0 && map[y - 1][x] != '1') {
      newY = y - 1;  // Mover para cima
    }
    else if(input == 's' && y < 49 && map[y + 1][x] != '1') {
      newY = y + 1;  // Mover para baixo
    }


      // Atualizar a posição do elemento "x" se for diferente da posição atual
    if (newX != x || newY != y) {
    x = newX;
    y = newY;

      if(map[y][x] == 'T'){
        personagem.vida_personagem -= 5;
        map[y][x] = ' '; // Alterar '2' para espaço em branco
      }
      else if (map[y][x] == 'H'){
        personagem.vida_personagem += 2;
        map[y][x] = ' ';  // Alterar '3' para espaço em branco
      }
      else if (personagem.profissao == 1 && map[y][x] == 'A') {
        personagem.forca += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 2 && map[y][x] == 'A') {
        personagem.inteligencia += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (personagem.profissao == 3 && map[y][x] == 'A') {
        personagem.destreza += 5;
        map[y][x] = ' ';  // Alterar '4' para espaço em branco
      }
      else if (map[y][x] == 'V') {
        turno_mais_visao = 17;  // Definir o tempo de duração do campo de visão expandido em segundos
        map[y][x] = ' ';  // Alterar '5' para espaço em branco
      }
      else if (map[y][x] == 'C'){
        chefao(personagem);
        break;
      }
    }

    // Reduzir o tempo de duração do campo de visão expandido a cada iteração
    if (turno_mais_visao > 0) {
       turno_mais_visao--;
    }
    if (personagem.vida_personagem <= 0) {  //  Caso a vida chegue a 0, o jogo acaba
      printf("\n\nGAME OVER !\n");
      break;  // Encerrar o jogo
    }
  }
}
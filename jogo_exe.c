#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mapas.c"
#include "menu_rpg.h"

void iniciarJogo(struct Personagem personagem){
  int dificuldade_jogo;
  srand(time(NULL));
  int random_mapa = rand() % 2;
  system("clear");
  printf("JOGO INICIADO!!!\n\n");
  
  printf("\nO seu objetivo é achar o chefão que está\n");
  printf("em algum lugar no labirinto. Encontre-o\n");
  printf("e o derrote. Boa sorte!\n\n");
  printf("Vamos ver se você é FORTE...\n");
  printf("ou FRACO...\n\n");
  printf("Escolha a dificuldade do jogo:\n1 - Fácil\n2 - Normal\n3 - Difícil\n");
    scanf("%d", &dificuldade_jogo);
      int mapa_escolhido;
      if(dificuldade_jogo == 1){
        if(random_mapa == 0){
          mapa_1_1(personagem);
        }
        else if(random_mapa != 0){
          mapa_1_1(personagem);
        }
      }

      else if(dificuldade_jogo == 2){
        if(random_mapa == 0){
          mapa_2_1(personagem);
        }
        else if(random_mapa != 0){
          mapa_2_2(personagem);
        }
      }

      else if (dificuldade_jogo == 3){
        if(random_mapa == 0){
          mapa_3_1(personagem);
        }
        else if(random_mapa != 0){
          mapa_3_2(personagem);
        }
      }

      else{
        iv();
      }

}

int main(){

  menu();

    int opcao;  
    int personagemCriado = 0;   // Definimos personagemCriado = 0, caso o jogador tente começar o jogo sem criar o personagem.
    struct Personagem personagem;     // Utilizamos o "struct Personagem" para armazenar todas as caracteristicas do personagem.

    while (opcao != 3) {    // Usamos while para para criar um loop para imprimir o menu novamente se a opção não for aceita.
      printf("Escolha uma opção:\n");
      printf("1. Criar Personagem\n");
      printf("2. Iniciar Jogo\n");
      printf("0. Sair\n");
      scanf("%d", &opcao);

        if (opcao == 1) {   // Aqui direcionamos o jogador para "void criarPersonagem" para a criação do personagem.
          criarPersonagem(&personagem);
          personagemCriado = 1;   // Se a opção = 1, definimos que o personagem foi criado atribuindo personagemCriado = 1.
        }

        else if(opcao == 2){
          if (personagemCriado == 1) {    // O jogo será iniciado se personagemCriado = 1.
            iniciarJogo(personagem);
            } else {    // Se personagemCriado = 0, o jogo não será iniciado, e retornará para o menuå
              printf("\nCrie um personagem antes\n");
              printf("de iniciar o jogo.\n");
          }
        }

        else if(opcao == 0){    // Aqui o jogo será fechado se opcao = 3.
          printf("Saindo do jogo...\n");
          break;
        }
        
        else{   // Usamos "else" para mostrar que opção colocada foi inválida, e retorna para "while".
          iv();
        }
            
      printf("\n");
    }

  return 0;
}
#ifndef C_PERSONAGEM_H
#define C_PERSONAGEM_H
#include <stdio.h>
#include <time.h>
#include "op_iv.h"
// struct usado para definir as caracteristicas do personagem
// uma vez definidas podemos usa-las para definir certas interações
struct Personagem {
  char nome[21];
  int raca;
  int alinhamento;
  int profissao;
  char historia[400];
  int porte;
  int forca;
  int destreza;
  int inteligencia;
  int constituicao;
  int vida_personagem;
};

// usamos void criarPersonagem para direcionar
// o jogador atraves do menu para a definição 
// das caracteristicas do personagem

void criarPersonagem(struct Personagem *personagem) {
  printf("\n=== Criação de Personagem ===\n");
  printf("Qual o seu nome: ");
    scanf("%s", personagem->nome);

  loop1:    // Usamos o "loop" e "goto" para retornar a raça, se a opção digitada for incorreta
  printf("\nDigite a Raça do personagem:\n");
  printf("1 - Humano\n");
  printf("2 - Anão\n");
  printf("3 - Elfo\n");
    scanf("%d", &personagem->raca);
  if(personagem->raca < 1 || personagem->raca > 3){
    iv();
    goto loop1;
  }

  loop2:    // Usamos o "loop" e "goto" para retornar ao alinhamento, se a opção digitada for incorreta
  printf("\nDigite o Alinhamento do\n");
  printf("personagem:\n");
  printf("1 - Mal\n");
  printf("2 - Neutro\n");
  printf("3 - Bom\n");
    scanf("%d", &personagem->alinhamento);
  if(personagem->alinhamento < 1 || personagem->alinhamento > 3){
    iv();
    goto loop2;
  }

  loop3: // Usamos o "loop" e "goto" para retornar a profissão, se a opção digitada for incorreta
  if(personagem->alinhamento == 3){   // Aqui foi criado um restrição para o alinhamento = 3, podendo escolher a profissão entre guerreiro ou mago
    printf("\nDigite a Profissão:\n");
    printf("1 - Guerreiro\n");
    printf("2 - Mago\n");
      scanf("%d", &personagem->profissao);
    if(personagem->profissao > 2 || personagem->profissao < 1){
      iv();
      goto loop3;
    }
  } else {    // se o alinhamento for diferente de 3, pode pode escolher todas as opções
    printf("\nDigite o Profissão:\n");
    printf("1 - Guerreiro\n");
    printf("2 - Mago\n");
    printf("3 - Ladino\n");
      scanf("%d", &personagem->profissao);
    if(personagem->profissao < 1  || personagem->profissao > 3){
      iv();
      goto loop3;
    }
  }

  loop4:    // Usamos o "loop" e "goto" para retornar a porte, se a opção digitada for incorreta
  if(personagem->raca == 2){    // Aqui foi criado um restrição para o raca = 2, podendo escolher o porte entre médio é pequeno
    printf("\nDigite o Porte:\n");
    printf("2 - Medio\n");
    printf("3 - Pequeno\n");
      scanf("%d", &personagem->porte);
    if(personagem->porte < 2 || personagem->porte > 3){
      iv();
      goto loop4;
    }
  } else {    // se a raca for diferente de 2, pode pode escolher todas as opções
    printf("\nDigite o Porte:\n");
    printf("1 - Grande\n");
    printf("2 - Medio\n");
    printf("3 - Pequeno\n");
      scanf("%d", &personagem->porte);
    if(personagem->porte < 1 || personagem->porte > 3){
      iv();
      goto loop4;
    }
  }

  printf("\nHora de escolher seus atributos. Mas atenção,");
  printf("a soma dos seus atributos deve ser maior que 10.\n\n");
  int soma_atributos = 0;

  loop5:
  printf("\nQuanto de força você tem?\n");
  printf("(Escolha de um valor de 1 a 5)\n");
    scanf("%d", &personagem->forca);
    
  if (personagem->forca < 1 || personagem->forca > 5){
    iv();
    goto loop5;
  }

  soma_atributos = personagem->forca;

  printf("\nA soma dos atributos é igual a %d.\n\n", soma_atributos);

  loop6:
  printf("\nQuanto de destreza você tem?\n");
  printf("(Escolha um valor entre 1 a 5)\n");
    scanf("%d", &personagem->destreza);
  
  if(personagem->destreza < 1 || personagem->destreza > 5){
    iv();
    goto loop6;
  }

  soma_atributos += personagem->destreza;

  printf("\nA soma dos atributos é igual a %d.\n\n", soma_atributos);

  loop7:
  printf("\nQuanto de inteligêcia você tem?\n");
  printf("(Escolha um valor entre 1 a 5)\n");
    scanf("%d", &personagem->inteligencia);
  
  if(personagem->inteligencia < 1 || personagem->inteligencia > 5){
    iv();
    goto loop7;
  }

  soma_atributos += personagem->inteligencia;

  printf("\nA soma dos atributos é igual a %d.\n\n", soma_atributos);

  loop8:
  printf("\nQuanto de contituição você tem?\n");
  printf("(Escolha um valor entre 1 a 5)\n");
    scanf("%d", &personagem->constituicao);
  
  if(personagem->constituicao < 1 || personagem->constituicao > 5){
    iv();
    goto loop8;
  }

  soma_atributos += personagem->constituicao;

  printf("\nA soma dos atributos é igual a %d.\n\n", soma_atributos);

  if (soma_atributos > 10){
    printf("A soma dos atributos foi maior que 10.\n");
    printf("Tente mais uma vez.\n");
    goto loop5;
  }

    if(personagem->raca == 3){
      printf("Como você escolheu a raça Elfo, você terá\n");
      printf("+1 de destreza e -1 de constituição.\n");
      personagem->destreza = personagem->destreza + 1;
      personagem->constituicao = personagem->constituicao - 1;
    }

    if(personagem->raca == 2){
      printf("Como você escolheu a raça Anão, você terá\n");
      printf("+1 de força e -1 de destreza.\n");
      personagem->forca = personagem->forca + 1;
      personagem->destreza = personagem->destreza - 1;
    }

    if(personagem->profissao == 2){
      printf("Como você escolheu a profissão Mago, você terá\n");
      printf("+1 de inteligência e -2 de força.\n");
      personagem->inteligencia = personagem->inteligencia + 1;
      personagem->forca = personagem->forca - 2;
    }

    if(personagem->profissao == 3){
      printf("Como você escolheu a profissão Ladino, você terá\n");
      printf("+1 de destreza, -1 de força e -1 de inteligência.\n");
      personagem->destreza = personagem->destreza + 1;
      personagem->forca = personagem->forca - 1;
      personagem->inteligencia = personagem->inteligencia - 1;
    }

  personagem->vida_personagem = personagem->constituicao * 20;
  if(personagem->constituicao == 0){
    personagem->vida_personagem = 10;
  }
  
  printf("\n=== * Personagem  criado * ===\n");
  printf("====== * com sucesso! * ======\n\n");
  printf("Sua vida é igual a: %d", personagem->vida_personagem);

}
#endif
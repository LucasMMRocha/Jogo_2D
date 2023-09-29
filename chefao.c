#include <stdio.h>
#include "c_personagem.h"

void chefao(struct Personagem personagem){
  int vitorias1 = 0;
  printf("HORA DO CHEFAO JOGADOR\n\n");
  printf("Desafio de Jokenpô!\n");
  while (vitorias1 < 3 && personagem.vida_personagem > 0){
    printf("Escolha: 1 - Pedra, 2 - Papel, 3 - Tesoura\n");
    int escolha_jogador;
    scanf("%d", &escolha_jogador);
    system("clear");

    srand(time(0));
    int escolha_computador = rand() % 3 + 1;

    if (escolha_jogador == escolha_computador) {
      printf("\nEmpate!\n");
      printf("Vitórias: %d\nVida: %d\n\n", vitorias1, personagem.vida_personagem);
    } else if ((escolha_jogador == 1 && escolha_computador == 3) || 
              (escolha_jogador == 2 && escolha_computador == 1) ||
              (escolha_jogador == 3 && escolha_computador == 2)) {
      printf("\nVocê ganhou!\n");
      vitorias1++;
      printf("Vitórias: %d\nVida: %d\n\n", vitorias1, personagem.vida_personagem);
    } else {
      printf("\nVocê perdeu!\n");
      personagem.vida_personagem--;
      printf("Vitórias: %d\nVida: %d\n\n", vitorias1, personagem.vida_personagem);
    }
  }

  int vitorias2 = 0;

  srand(time(NULL));    // "srand(time(NULL))" é utilizado para criar um numero aleátorio.

  printf("Hora das charadas!!!\n");

  while (vitorias2 < 2 && personagem.vida_personagem > 0) {   // Utilizamos um "while" para criar um loop enquanto o jogador não vencer 3 vezes, ou a vida dele for maior que 0.
    // Sortear três charadas aleatórias
    // Em charadaIndex1/2/3 = rand() % 10, escolhemos um número de 1 ate 10 para escolher uma das 10 charadas.
    int charadaIndex1 = rand() % 10;
    int charadaIndex2, charadaIndex3;

    // Utilizamos "do" e "while" junto com charadaIndex2/3 para que as charadas não se repitam.

    do {
        charadaIndex2 = rand() % 10;
    } while (charadaIndex2 == charadaIndex1);

    do {
        charadaIndex3 = rand() % 10;
    } while (charadaIndex3 == charadaIndex1 || charadaIndex3 == charadaIndex2);

    char *charadas[10] = {    // Aqui foi criado um "char" para armazenar todas as 10 charadas, que poderão ser escolhidas atravez de charadaIndex1/2/3.
      "\nO que é, o que é?\nSem sair do seu cantinho, é capaz de viajar ao redor do mundo.\n\n1- O selo\n2- O carro\n3- O jardim\n",
      "\nO que é, o que é?\nÉ feito de água, mas se for colocado dentro da água morrerá.\n\n1- A tesoura\n2- Cachoeira\n3- O gelo\n",
      "\nO que é, o que é?\nÉ alta quando jovem e baixinha quando fica velha. Além disso, é rápida quando é magra e lenta quando é gorda.\n\n1- O mouse\n2- A panela\n3- A vela\n",
      "\nO que é, o que é?\nPode ser atirado do alto de um prédio e ficar super bem. Mas quando é colocado na água morre pouco tempo depois.\n\n1- O papel\n2- A caneta\n3- O celular\n",
      "\nO que é, o que é?\nFica cada vez mais molhado quanto mais a gente seca.\n\n1- O picolé\n2- A toalha\n3- A fogueira\n",
      "\nO que é, o que é?\nVocê pode pegar, mas não pode jogar.\n\n1- Toalha\n2- O papel\n3- Resfriado\n",
      "\nO que é, o que é?\nÉ mais leve que uma pluma, mas nem o homem mais forte do mundo pode segurá-la por mais de um minuto.\n\n1- Resfriado\n2- A respiração\n3- A tesoura\n",
      "\nO que é, o que é?\nSobe, sobe, sobe e jamais desce.\n\n1- O escorregador\n2- A montanha-russa\n3- A idade\n",
      "\nO que é, o que é?\nEstá sempre a caminho, mas nunca chega.\n\n1- Ontem\n2- Hoje\n3- Amanhã\n",
      "\nO que é, o que é?\nTem cidades, mas não tem casas. Tem montanhas, mas não tem árvores. Tem água, mas não tem peixe.\n\n1- O mapa\n2- A bússola\n3- O rato\n"
    };

    printf("\nResponda às seguintes charadas:\n");
    printf("%s", charadas[charadaIndex1]);    // Aqui utlizamos charadas[charadaIndex1] para acessar uma das 10 charadas.

    int resposta1;
    printf("Digite sua resposta (1, 2 ou 3): ");
    scanf("%d", &resposta1);

    if (resposta1 < 1 || resposta1 > 3) {     // Foi criado um "if" caso a opção não seja válida.
      iv();
      continue;
    }

    printf("%s", charadas[charadaIndex2]);

    int resposta2;
    printf("Digite sua resposta (1, 2 ou 3): ");
    scanf("%d", &resposta2);

    if (resposta2 < 1 || resposta2 > 3) {     // Foi criado um "if" caso a opção não seja válida.
      iv();
      continue;
    }

    printf("%s", charadas[charadaIndex3]);
    
    int resposta3;
    printf("Digite sua resposta (1, 2 ou 3): ");
    scanf("%d", &resposta3);

    if (resposta3 < 1 || resposta3 > 3) {     // Foi criado um "if" caso a opção não seja válida.
      iv();
      continue;
    }

    // Respostas corretas das charadas em na mesma ordem 
    int respostasCorretas[10] = {1, 3, 3, 1, 2, 3, 2, 3, 3, 1};

    int pontosPerdidos = 0;

    if (resposta1 != respostasCorretas[charadaIndex1]) {    // Caso a resposta não esteja correta, soma-se 50 nos pontosPerdidos.
      printf("Resposta 1 incorreta! -1 pontos de vida.\n");
      personagem.vida_personagem--;
    }

    if (resposta2 != respostasCorretas[charadaIndex2]) {    // Caso a resposta não esteja correta, soma-se 50 nos pontosPerdidos.
      printf("Resposta 2 incorreta! -1 pontos de vida.\n");
      personagem.vida_personagem--;
    }

    if (resposta3 != respostasCorretas[charadaIndex3]) {    // Caso a resposta não esteja correta, soma-se 50 nos pontosPerdidos.
      printf("Resposta 3 incorreta! -1 pontos de vida.\n");      
      personagem.vida_personagem--;
    }

    system("clear");

    printf("\nParabéns! Você acertou todas as charadas.\n");
    printf("Vida: %d\n", personagem.vida_personagem);
          
    printf("\nParabêns!!! Você derrotou\n");
    printf("o chefão. Obrigado por jogar\n");
    printf("o meu jogo. Fique a vontade\n");
    printf("para tentar outros modos e\n");
    printf("niveis de jogo!\n\n");
    break;
  }
}
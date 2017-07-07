
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include"estruturas.h"
#include"graphs.h"
#include"data.h"

setting read_setting()
{
  FILE *fp = NULL;
  char linha[MAX_STRING] = {0}, *aux;
  setting config;

  //lê ficheiro e testa dse foi lido com sucesso
  fp = fopen("settings.txt","r");
  if(fp == NULL)
  {
    printf("Ficheiro com configurações não exitente ou com erros\n");
    exit(EXIT_FAILURE);
  }

  while (fgets(linha, MAX_STRING,fp) != NULL)
  {
    //ler with
    aux = strtok(linha,",");
    if(aux == NULL)
    {
      printf("Ficheiro com configurações não exitente ou com erros\n");
      exit(EXIT_FAILURE);
    }
    config.with = atoi(aux);

    //ler height
    aux = strtok(NULL,",");
    if(aux == NULL)
    {
      printf("Ficheiro com configurações não exitente ou com erros\n");
      exit(EXIT_FAILURE);
    }
    config.height = atoi(aux);

    //ler with_squares
    aux = strtok(NULL,",");
    if(aux == NULL)
    {
      printf("Ficheiro com configurações não exitente ou com erros\n");
      exit(EXIT_FAILURE);
    }
    config.with_squares = atoi(aux);

    //ler size
    aux = strtok(NULL,",");
    if(aux == NULL)
    {
      printf("Ficheiro com configurações não exitente ou com erros\n");
      exit(EXIT_FAILURE);
    }
    config.size = atoi(aux);

    //ler speed
    aux = strtok(NULL,",");
    if(aux == NULL)
    {
      printf("Ficheiro com configurações não exitente ou com erros\n");
      exit(EXIT_FAILURE);
    }
    config.speed = atoi(aux);
  }

  return config;
}

lagarta *inciar_lagarta(setting config)
{
  lagarta *head;
  head = NULL;

  for (int i = 0; i < config.size;i++)
  {
    head = novo_no_lagarta(head, config);
  }
  return head;
}

lagarta *novo_no_lagarta(lagarta *head, setting config)
{
  lagarta *newNode = NULL;
  lagarta *aux = NULL;
	//allocar memória para o nó e verifica se foi bem alocada
	newNode = (lagarta *)malloc(sizeof(lagarta));
	if (newNode == NULL)
	{
		printf("Memory was NOT allocated. \n");
		exit(EXIT_FAILURE);
	}

  if(head == NULL)
  {
    //primeiro elemento
    newNode->actual.x = config.with/2;
    newNode->actual.y = config.height/2;
    newNode->old = newNode->actual;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
  }
  aux = head;
  while (aux->next!=NULL) {
    aux = aux->next;
  }

  newNode->actual.x = aux->old.x + config.with_squares;
  newNode->actual.y = aux->old.y;
  newNode->old = newNode->actual;
  newNode->prev = aux;
  newNode->next = NULL;
  aux->next = newNode;
  return head;
}

lagarta *atualizar_lagarta(ponto velocidade, lagarta *head, setting config)
{
  lagarta *aux = NULL;

  aux = head;
  aux->actual.x = velocidade.x*config.with_squares + aux->old.x;
  aux->actual.y = velocidade.y*config.with_squares + aux->old.y;
  aux = aux->next;
  while (aux!=NULL) {
    aux->actual.x = aux->prev->old.x;
    aux->actual.y = aux->prev->old.y;
    aux = aux->next;
  }
  return head;
}

lagarta *atualizar_lagarta_old(lagarta *head)
{
  lagarta *aux = NULL;

  aux = head;

  while (aux!=NULL) {
    aux->old.x = aux->actual.x;
    aux->old.y = aux->actual.y;
    aux = aux->next;
  }
  return head;
}

int colisao_margens(lagarta *head, setting config)
{
  if(head->actual.x < 0 || head->actual.x >config.with)
    return 1;

  if(head->actual.y < 0 || head->actual.y >config.height)
    return 1;

  lagarta *aux = NULL;
  aux = head->next;
  while (aux != NULL) {
    if(head->actual.x == aux->actual.x && head->actual.y == aux->actual.y)
      return 1;
    aux = aux->next;
  }

  return 0;
}

lagarta *free_lagarta(lagarta *head)
{
  lagarta *aux = NULL;

  while (head!=NULL) {
    aux = head;
    head = head->next;
    free(aux);
  }
  return head;
}

ponto comida(lagarta **head, ponto comida_lagarta, setting config)
{
  srand(time(NULL));
  if((*head)->actual.x == comida_lagarta.x && (*head)->actual.y == comida_lagarta.y)
  {
    *head = novo_no_lagarta(*head,config);
    comida_lagarta.x = config.with_squares*(rand()%(config.with/config.with_squares));
    comida_lagarta.y = config.with_squares*(rand()%(config.height/config.with_squares));
  }
  return comida_lagarta;
}

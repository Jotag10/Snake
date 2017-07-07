
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

int main(int agrc, char* argv[])
{
  setting definicoes;
  lagarta *head_lagarta;
  head_lagarta = NULL;

  definicoes = read_setting();

  head_lagarta = inciar_lagarta(definicoes);

  main_graphic(head_lagarta, definicoes);
}

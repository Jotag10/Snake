
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

/**
 * main_graphic: função que executa toda a parte gráfica
 * \param lista_viagens ponteiro para a cabeça da lista de viagens
 * \param lista_estacoes ponteiro para a cabeça da lista de estações
 * \param argv vetor de strings com os argumentos
 */
void main_graphic(lagarta *head, setting config)
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Event event;
  TTF_Font *font1 = NULL;
  TTF_Font *font2 = NULL;
  int delay = config.speed;
  int quit = 0;
  int width = config.with;//largura da janela
  int height = config.height;//altura da janela
  int perdeu = 0;

  ponto velocidade;
  velocidade.x = -1;
  velocidade.y = 0;
  srand(time(NULL));

  ponto vamos_comer;

  vamos_comer.x = config.with_squares*(rand()%(config.with/config.with_squares));
  vamos_comer.y = config.with_squares*(rand()%(config.height/config.with_squares));

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  // initialize graphics
  InitEverything(width, height, &font1, &font2, &window, &renderer);

  while( quit == 0 )
  {
    // while there's events to handle
    while( SDL_PollEvent( &event ) )
    {
      if( event.type == SDL_QUIT )//esta tecla é a cruz presente no canto superior direito da janela do programa que fecha a janela
      {
        quit = 1;
      }
      else if ( event.type == SDL_KEYDOWN )
      {
        switch ( event.key.keysym.sym )
        {
          case SDLK_q: //se carregar na letra q (minúscula), a janela do jogo fecha
            quit = 1;
          break;
          case SDLK_r: //se carregar na letra q (minúscula), a janela do jogo fecha
            perdeu = 0;
          break;
          case SDLK_RIGHT: //se carregar na seta para a direta
            if (velocidade.x == 0) {
              velocidade.x = 1;
              velocidade.y = 0;
            }
          break;
          case SDLK_LEFT: //se carregar na seta para a esquerda
          if (velocidade.x == 0) {
            velocidade.x = -1;
            velocidade.y = 0;
          }
          break;
          case SDLK_UP: //se carregar na seta para a direta
          if (velocidade.y == 0) {
            velocidade.x = 0;
            velocidade.y = -1;
          }
          break;
          case SDLK_DOWN: //se carregar na seta para a esquerda
          if (velocidade.y == 0) {
            velocidade.x = 0;
            velocidade.y = 1;
          }
          break;
        }
      }
    }



    if(perdeu == 0)
    {
      perdeu = colisao_margens(head, config);
      if(perdeu == 0)
      {

        SDL_RenderClear(renderer);

        render_lagarta(head, config, renderer, vamos_comer);

        head = atualizar_lagarta_old(head);

        vamos_comer = comida(&head, vamos_comer,config);

        head = atualizar_lagarta(velocidade, head, config);
      }

    }
    if(perdeu == 1)
    {
      head = free_lagarta(head);
      head = inciar_lagarta(config);
      velocidade.x = -1;
      velocidade.y = 0;
    }
    // render in the screen all changes above
    SDL_RenderPresent(renderer);
    // add a delay
    SDL_Delay( delay );
  }
  TTF_CloseFont(font1);
  TTF_CloseFont(font2);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

/**
 * InitEverything: Initializes the SDL2 library and all graphical components: font, window, renderer
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _font font that will be used to render the text
 * \param _img surface to be created with all images
 * \param _window represents the window of the application
 * \param _renderer renderer to handle all rendering in a window
 */
void InitEverything(int width, int height, TTF_Font **_font1, TTF_Font **_font2 , SDL_Window** _window, SDL_Renderer** _renderer)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height);
    *_renderer = CreateRenderer(width, height, *_window);

    //font1
    *_font1 = TTF_OpenFont("FreeSerif.ttf", 25);
    if(!*_font1)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    //font2
    *_font2 = TTF_OpenFont("FreeSerif.ttf", 16);
    if(!*_font2)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitSDL: Initializes the SDL2 graphic library
 */
void InitSDL()
{
    // init SDL library
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
	}
}

/**
 * InitFont: Initializes the SDL2_ttf font library
 */
void InitFont()
{
	// Init font library
	if(TTF_Init()==-1)
	{
	    printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
	}
}

/**
 * CreateWindow: Creates a window for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \return pointer to the window created
 */
SDL_Window* CreateWindow(int width, int height)
{
    SDL_Window *window;
    // init window
	window = SDL_CreateWindow( "SNAKE", WINDOW_POSX, WINDOW_POSY, width, height, 0 );
    // check for error !
	if ( window == NULL )
	{
		printf("Failed to create window : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	return window;
}

/**
 * CreateRenderer: Creates a renderer for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _window represents the window for which the renderer is associated
 * \return pointer to the renderer created
 */
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
	renderer = SDL_CreateRenderer( _window, -1, 0 );

	if ( renderer == NULL )
	{
		printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
	}

	// set size of renderer to the same as window
	SDL_RenderSetLogicalSize( renderer, width, height );

	return renderer;
}

/**
 * RenderText function: Renders some text on a position inside the app window
 * \param x X coordinate of the text
 * \param y Y coordinate of the text
 * \param text string with the text to be written
 * \param _font TTF font used to render the text
 * \param _color color of the text
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;
	SDL_Rect solidRect;

	solidRect.x = x;
	solidRect.y = y;
    // create a surface from the string text with a predefined font
	text_surface = TTF_RenderText_Blended(_font,text,*_color);
	if(!text_surface)
	{
	    printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
	    exit(EXIT_FAILURE);
	}
    // create texture
	text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
	SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
	SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
	SDL_DestroyTexture(text_texture);
	SDL_FreeSurface(text_surface);
	return solidRect.h;
}

void render_lagarta(lagarta *head, setting config, SDL_Renderer *_renderer, ponto comer)
{
  lagarta *aux = NULL;

  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

  aux = head;
  SDL_Rect no_lagarta; //retangulo representa cada nó da lagarta
  while (aux!=NULL) {
    no_lagarta.x = aux->actual.x;
    no_lagarta.y =aux->actual.y;
    no_lagarta.w =config.with_squares;
    no_lagarta.h =config.with_squares;
    SDL_RenderFillRect(_renderer, &no_lagarta);
    aux = aux->next;
  }

  no_lagarta.x = comer.x;
  no_lagarta.y =comer.y;
  no_lagarta.w =config.with_squares;
  no_lagarta.h =config.with_squares;
  SDL_RenderFillRect(_renderer, &no_lagarta);

  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

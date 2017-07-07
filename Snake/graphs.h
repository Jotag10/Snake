
void main_graphic(lagarta *head, setting config);

void InitEverything(int width, int height, TTF_Font **_font1, TTF_Font **_font2 , SDL_Window** _window, SDL_Renderer** _renderer);

void InitSDL();

void InitFont();

SDL_Window* CreateWindow(int width, int height);

SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window);

int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer);

void render_lagarta(lagarta *head, setting config, SDL_Renderer *_renderer, ponto);

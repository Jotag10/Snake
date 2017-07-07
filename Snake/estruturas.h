typedef struct{
  int with;
  int height;
  int with_squares;
  int size;
  int speed;
}setting;

typedef struct{
  int x;
  int y;
}ponto;

typedef struct node{
  ponto actual;
  ponto old;
  struct node *next;
  struct node *prev;
}lagarta;

#define WINDOW_POSX 200       // initial position of the window: x
#define WINDOW_POSY 200       // initial position of the window: y
#define MAX_STRING 200

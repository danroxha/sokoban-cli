#ifndef __TYPES_SOKOBAN_H__
#define __TYPES_SOKOBAN_H__

#define BOX    '#'
#define WALL   '*'
#define DOLL   '@'
#define TARGET '?'

enum {
	MENU_CONTINUE    = 1,
	MENU_NEW_GAME    = 2,
	MENU_HOW_TO_PLAY = 3, 
	MENU_EXIT        = 4
};

typedef struct error{
  char *message;
  char *type;
} Error;

typedef struct errors {
  Error *list;
  bool hasError;
  int size;
} Errors;

typedef struct object {
  int x, y;
  char body;
} Object;

typedef struct box {
  int x, y;
  int id;
  char body;
  bool enable;
} Box;

typedef struct goals {
  Object *list;
  int lenght;
} Goals;

typedef struct boxes{
  Box *list;
  int lenght;
} Boxes;

typedef struct map {
  char **field;
  int width;
  int height;
  Errors errors;

} Map;

typedef struct gameState {
  Boxes *boxes;
  Goals *goals;
  Map currrentMap;
  Object *character;
  bool win;
  int level;
  int time;
} GameState;

typedef struct levels {
  char **filenames;
  char **paths;
  int total;

} Levels;

typedef struct world {
  Levels *levels;
  int total;
} World;

typedef struct screen {
	int width, height;
	int centerWidth, centerHeight;
} Screen;

typedef struct cursor {
  int x, y;
  char pointer;
} Cursor;


typedef struct program {
	bool running;
} Program;


typedef struct savestate {
	int world;
	int level;
	char* path;
} SaveState;


#endif // __TYPES_SOKOBAN_H__
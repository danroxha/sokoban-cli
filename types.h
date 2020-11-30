#ifndef __TYPES_SOKOBAN_H__
#define __TYPES_SOKOBAN_H__

#define BOX    '#'
#define WALL   '*'
#define DOLL   '@'
#define TARGET '?'


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
  int lenght;
  Object *list;
} Goals;

typedef struct {
  Box *list;
  int lenght;
} Boxes;

typedef struct map {
  char **field;
  int width;
  int height;

} Map;

typedef struct gameState {
  Boxes *boxes;
  Map currrentMap;
  Object *character;
  bool gameOver;
  int level;
} GameState;

#endif // __TYPES_SOKOBAN_H__
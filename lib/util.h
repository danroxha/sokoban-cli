#ifndef __UTIL_SORT_H__
#define __UTIL_SORT_H__

#include <string.h>
#include <stdlib.h>

static int compare(const void* a, const void* b)  { 
  return strcmp(*(const char**)a, *(const char**)b); 
} 

static int compareLevels(const void* a, const void* b)  {
  return strcmp((*(Levels*)a).paths[0] , (*(Levels*)b).paths[0]);
} 

void sortWorld(Levels *levels, int n){  
  qsort(levels, n, sizeof(Levels), compareLevels);
}

void sort(char** arr, int n) { 
  qsort(arr, n, sizeof(const char*), compare); 
}

#endif // __UTIL_SORT_H__

#ifndef __UTIL_ERROR_H__
#define __UTIL_ERROR_H__

#include <errno.h>
#include "screen.h"

void throw_message(const char*, char*);


#define try bool __HadError=false;
#define catch(x) ExitJmp:if(__HadError)
#define throw(x) __HadError=true;goto ExitJmp;


void throw_message(const char* message, char* color) {
  
  show_cursor();
  text_color(color);
  reset_video();
  fprintf(stderr, "\r%s", message);
  close_keyboard();
  exit(1);
}

#endif // __UTIL_ERROR_H__

#ifndef __UTIL_DIR_H__
#define __UTIL_DIR_H__

#include <dirent.h>
#include <stdbool.h>

bool isdir(const char *);

bool isdir(const char *name){
  
  DIR *dir = opendir(name);

  if(dir != NULL) {
    closedir(dir);
    return true;
  }

  if(errno == ENOTDIR)
    return false;

  return false; 
    
}

#endif // __UTIL_DIR_H__

#ifndef __UTIL_TEST_H__
#define __UTIL_TEST_H__


#include <string.h>
#include "types.h"
#include "util.h"
#include "../src/map.h"

void has_issue_in_maps_file(const char*);


void has_issue_in_maps_file(const char* dirname) {
   
  World world = load_worlds(dirname);
  Map map;

  printf("\n☑  \033[34;1mVALIDATE MAPS\033[0;0m\n");
  
  for(int i = 0; i < world.total; i++) {
    printf("\033[37;1mWorld: %d - size: %d\033[0;0m\n", i + 1, world.levels[i].total);
    for(int j = 0; j < world.levels[i].total; j++)
    {
      try {

        map = load_map(world.levels[i].paths[j]);

        if(map.errors.has_error) {
          throw();
        }

        printf("\033[32;1m ✔ \033[0;0m Level: %s\n", world.levels[i].paths[j]);

      }
      catch(...) {

        fprintf(stderr, "\033[31;1m ⨯ \033[0;0m Level: %s\n", world.levels[i].paths[j]);
        fprintf(stderr, "    %s\n", map.errors.list[0].type);
        for(int i = 0; i < map.errors.size; i++)
          fprintf(stderr, "\t%s\n", map.errors.list[i].message);
      }
    }
  }

  destroy(&world, "World");
  destroy(&map, "Map");
}

#endif // __UTIL_TEST_H__


#ifndef __UTIL_FREE_H__
#define __UTIL_FREE_H__


#include <string.h>
#include <stdlib.h>
#include "types.h"

void destroy(void*, const char*);

void destroy(void *memory, const char* type) {
  if(!strcmp(type, "Map")) {
    Map *map = (Map*) memory;
    for(int i = 0; i < map->height; i++) {
      map->field[i] = NULL;
      free(map->field[i]);
    }

    free(map->field);
    map->field = NULL;

    return;
  } 

  if(!strcmp(type, "Levels")) {
    Levels *levels = (Levels*) memory;
    
    for(int i = 0; i < levels->total; i++) {
      if(!levels->filenames) free(levels->filenames);
      if(!levels->paths) free(levels->paths);
    }

    return;
  }

  if(!strcmp(type, "World")) {
  	World *world = (World*) memory;

  	for(int i = 0; i < world->total; i++) {
  		destroy(&world->levels[i], "Levels");
  	}

  	if(world->levels != NULL) {
  		free(world->levels);
    }

    return;
  }

  if(!strcmp(type, "Boxes")) {
    Boxes *boxes = (Boxes*) memory;
    
    if(boxes->list != NULL) {
      free(boxes->list);
    }

    return;
  }

  if(!strcmp(type, "Goals")) {
    Goals *goals = (Goals*) memory;

    if(goals->list != NULL) {
      free(goals->list);
    }

    return;
  }

  if(!strcmp(type, "GameState")) {
    GameState *gameState = (GameState*) memory;

    if(gameState->current_map.field != NULL) {
      destroy(&gameState->current_map.field, "Map");
    }

    return;
  }

  if(!strcmp(type, "SaveState")) {
    SaveState *savestate = (SaveState*) memory;
    
    if(savestate->path) {
      free(savestate->path);
    }

    return;
  }

  fprintf(stderr, "\033[31;1mFILE: %s \n \033[0;1m", __FILE__);
  fprintf(stderr, "\033[31;1mError ↴\n  'destroy': Função 'destroy' recebeu tipo não registrado\n\033[0;1m");
  fprintf(stderr, "\033[32;1m   * Type :: '%s' \033[0;1m", type );
  exit(1);
}

#endif // __UTIL_TEST_H__

#ifndef __UTIL_NUMBER_H__
#define __UTIL_NUMBER_H__

int number_length(int number) {
  int size = 0;

  while(number /= 10) {
    size++;
  }

  return size;
}

#endif // __UTIL_NUMBER_H__
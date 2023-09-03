#ifndef __SAVESTATE_SOKOBAN_H__
#define __SAVESTATE_SOKOBAN_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../lib/screen.h"
#include "../lib/types.h"
#include "../lib/util.h"

SaveState load_save_state(const char*);
void define_save_state(SaveState);
void remove_save_state(const char*);
bool there_is_save_state(const char*);

SaveState load_save_state(const char* dirname) {

  SaveState save_state = {.world=0, .level=0, .path=NULL};
  const char* filename = "save_state.txt";
  const int mode = 0777;
  save_state.path = (char*) calloc(strlen(dirname) + strlen(filename), sizeof(char));

  if(save_state.path == NULL) {
    fprintf(stderr, "Error: memory isn't enough");
    exit(1);
  }

  sprintf(save_state.path ,"%s%s", dirname, filename);
  
  if(!isdir(dirname)) {
    mkdir(dirname, mode);
    FILE *file = fopen(save_state.path, "w");

    if(file == NULL) {
      free(save_state.path);
      text_color(IRED);
      fprintf(stderr, "Error: Nao foi possível carregar o arquivo de save_state em: %s", save_state.path);
      reset_video();
      exit(1);
     }

     fprintf(file, "%d %d", save_state.world, save_state.level);
     
    fclose(file);
    
    return save_state;
  }
  
  FILE *file = fopen(save_state.path, "r");

  if(file == NULL) {
    text_color(IRED);
    fprintf(stderr, "Error: Nao foi possível carregar o arquivo de save_state em: %s", save_state.path);
    reset_video();
    exit(1);
  }

  fscanf(file, "%d %d", &save_state.world, &save_state.level);
  fclose(file);
  
  return save_state;	
}

void define_save_state(SaveState save_state) {

  FILE* file = fopen(save_state.path, "w");

  if(file == NULL) {
    text_color(IRED);
    fprintf(stderr, "Error: Nao foi possível definir o arquivo de save_state em: %s", save_state.path);
    reset_video();
    exit(1);
  }
  
  fprintf(file, "%d %d", save_state.world, save_state.level);
  fclose(file);	
}

void remove_save_state(const char* dirname) {
  SaveState save_state = load_save_state(dirname);
  unlink(save_state.path);
  
  if(rmdir(dirname)) {
    clear();
    show_cursor();
    text_color(IRED);
    fprintf(stderr, "Error: Não foi possivel remover o save_state de: %s", dirname);
    reset_video();
    exit(1);
  }
}

bool there_is_save_state(const char* dirname) {
  return isdir(dirname);
}

#endif // __SAVESTATE_SOKOBAN_H__
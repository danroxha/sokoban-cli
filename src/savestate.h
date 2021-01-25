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


SaveState loadSaveState(const char* dirname);
void defineSaveState(SaveState savestate);
void removeSaveState(const char* dirname);
bool thereIsSavestate(const char* dirname);


SaveState loadSaveState(const char* dirname) {

	SaveState savestate = {.world=0, .level=0, .path=NULL};
	const char* filename = "savestate.txt";
	const int mode = 0777;
	savestate.path = (char*) calloc(strlen(dirname) + strlen(filename), sizeof(char));

	sprintf(savestate.path ,"%s%s", dirname, filename);
	
	if(!isdir(dirname)) {

		mkdir(dirname, mode);
	 	FILE *fileopen = fopen(savestate.path, "w");

	 	if(fileopen == NULL) {
      textcolor(IRED);
			fprintf(stderr, "Error: Nao foi possível carregar o arquivo de savestate em: %s", savestate.path);
			reset_video();
      exit(1);
	 	}

	 	fprintf(fileopen, "%d %d", savestate.world, savestate.level);
	 	
	  fclose(fileopen);
	  
	  return savestate;
	}

	
	FILE *fileopen = fopen(savestate.path, "r");

	if(fileopen == NULL) {
    textcolor(IRED);
		fprintf(stderr, "Error: Nao foi possível carregar o arquivo de savestate em: %s", savestate.path);
		reset_video();
    exit(1);
	}

	fscanf(fileopen, "%d %d", &savestate.world, &savestate.level);
	fclose(fileopen);
	
	return savestate;	
}


void defineSaveState(SaveState savestate) {

	FILE* fileopen = fopen(savestate.path, "w");

	if(fileopen == NULL) {
    	textcolor(IRED);
		fprintf(stderr, "Error: Nao foi possível definir o arquivo de savestate em: %s", savestate.path);
		reset_video();
    	exit(1);
	}
	
	fprintf(fileopen, "%d %d", savestate.world, savestate.level);
	fclose(fileopen);	
	
}

void removeSaveState(const char* dirname) {

	SaveState savestate = loadSaveState(dirname);
	unlink(savestate.path);
	
	if(rmdir(dirname)) {
		clear();
		showcursor();
    	textcolor(IRED);
		fprintf(stderr, "Error: Não foi possivel remover o savestate de: %s", dirname);
    	reset_video();
		exit(1);
	}
}

bool thereIsSavestate(const char* dirname) {
	return isdir(dirname);
}
#endif // __SAVESTATE_SOKOBAN_H__
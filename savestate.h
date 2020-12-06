#ifndef __SAVESTATE_SOKOBAN_H__
#define __SAVESTATE_SOKOBAN_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include "screen.h"
#include "types.h"
#include "util.h"


SaveState loadSaveState(const char* dirname);
void defineSaveState(SaveState savestate);



SaveState loadSaveState(const char* dirname) {

	SaveState savestate = {1, 1, NULL};
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


#endif // __SAVESTATE_SOKOBAN_H__
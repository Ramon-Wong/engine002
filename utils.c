#include "functions.h"








char *	ReadFile(const char * path){
	
	//~ usage										<==
	//~ 											<==
	//~ char * txt;									<==
	//~ 											<==	
	//~ txt = ReadFile("GLSL/loremipsum.txt");		<==
	//~ printf(" txt: %s", txt);					<==
	//~ free(txt);									<== memory leak
	//~ 											<==
	
	FILE *	tFile;
	char *	buffer;
	int		lSize;
	
	tFile = fopen( path, "rt");
	if(tFile){
		
		fseek( tFile, 0, SEEK_END);
		lSize = ftell( tFile);
		rewind( tFile);
		
		buffer = (char*) malloc( sizeof(char)*(lSize+1));
		fread( buffer, 1, lSize, tFile);
		buffer[lSize] = '\0';
		
		fclose(tFile);
	}else{
		printf("Error at opening file: %s", path);
	}
	
	return buffer;
}


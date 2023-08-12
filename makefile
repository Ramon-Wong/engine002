CC					= gcc
source				= main.c functions.c utils.c shaderutils.c matrix.c
objects				= main.o 
option				= -Wall
compile 			= -Wall -c
build				= -Wall -o
target				= main
executable			= ./main
library				= -lGLEW -lglfw -lGL - lGLU -lm


compile:
	$(CC) $(compile) $(source) $(library)

build:
	$(CC) $(build) $(target) $(objects) $(library)

run:
	$(executable)

clean:
	rm -f *.o $(target) a.out
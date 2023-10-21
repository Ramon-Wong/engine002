CC					= gcc
source				= main.c functions.c utils.c shaderutils.c renderutils.c matrix.c camera.c object.c framebuffer.c
objects				= main.o functions.o utils.o shaderutils.o renderutils.o matrix.o camera.o object.o framebuffer.o
option				= -Wall
compile 			= -Wall -c
build				= -Wall -o
target				= main
executable			= ./main
library				= -lm -lglfw -lGL -lGLU -lGLEW 


compile:
	$(CC) $(compile) $(source) $(library)

build:
	$(CC) $(build) $(target) $(objects) $(library)

run:
	$(executable)

clean:
	rm -f *.o $(target) a.out
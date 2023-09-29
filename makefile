CC					= gcc
source				= main.c functions.c shaderutils.c utils.c matrix.c
objects				= main.o functions.o shaderutils.o utils.o matrix.o
option				= -Wall
compile 			= -Wall -c
build				= -Wall -o
target				= main
executable			= ./main
library				= -lm -lglfw -lGL -lGLEW


compile:
	$(CC) $(compile) $(source) $(library)

build:
	$(CC) $(build) $(target) $(objects) $(library)

run:
	$(executable)

clean:
	rm -f $(objects) $(target) a.out
CC					= gcc
source				= main.c utils.c functions.c matrix.c
objects				= main.o utils.o functions.o matrix.o
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
	rm -f $(objects) $(target) a.out
CC					= gcc
valgrind			= valgrind
leak-check			= --leak-check=full
show-all			= --show-leak-kinds=all
source				= main.c functions.c utils.c shaderutils.c renderutils.c matrix.c camera.c object.c projections.c
objects				= main.o functions.o utils.o shaderutils.o renderutils.o matrix.o camera.o object.o projections.o
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

leak-test:
	$(valgrind) $(leak-check) $(executable)

full-leak-test:
	$(valgrind) $(leak-check) $(show-all) $(executable)

clean:
	rm -f *.o $(target) a.out
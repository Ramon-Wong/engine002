CC					= gcc
source				= main.c functions.c utils.c shaderutils.c matrix.c
objects				= main.o functions.o utils.o shaderutils.o matrix.o
option				= -Wall
compile 			= -Wall -c
build				= -Wall -o
target				= main
executable			= ./main
leaktest			= valgrind
library				= -lm -lglfw -lGL -lGLU -lGLEW 


compile:
	$(CC) $(compile) $(source) $(library)

build:
	$(CC) $(build) $(target) $(objects) $(library)

run:
	$(executable)

valgrind:
	$(leaktest) --leak-check=full -s $(executable)

clean:
	rm -f *.o $(target) a.out
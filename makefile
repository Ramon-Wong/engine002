CC					= g++
source				= main.c
objects				= main.o matrix.o
option				= -Wall
compile 			= -Wall -c
build				= -Wall -o
target				= main
executable			= ./main
library				= -lm -lglfw -lGL 


compile:
	$(CC) $(compile) $(source) $(library)

build:
	$(CC) $(build) $(target) $(objects) $(library)

clean:
	rm -f $(objects) $(target) a.out

run:
	$(executable)

clean:
	rm -f $(objects) $(target) a.out
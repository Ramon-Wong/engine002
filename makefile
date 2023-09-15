CC					= gcc
source				= main.c
objects				= *.o
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

run:
	$(executable)

clean:
	rm -f $(objects) $(target) a.out
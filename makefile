CC					= gcc
source				= main.c functions.c ShaderUtils.c Utils.c
objects				= main.o functions.o ShaderUtils.o Utils.o
option				= -Wall
compile 			= -Wall -c
build				= -Wall -o
target				= main
executable			= ./main
library				= -lm -lglfw -lGL -lGLEW


# gcc -Wall -o "%e" "%f" functions.c utils.c ShaderUtils.c Matrix4x.h -lm -lglfw -lGL -lGLEW  


compile:
	$(CC) $(compile) $(source) $(library)

build:
	$(CC) $(build) $(target) $(objects) $(library)

run:
	$(executable)

clean:
	rm -f $(objects) $(target) a.out
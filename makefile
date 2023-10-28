CC					= gcc
valgrind			= valgrind
leak-check			= --leak-check=full
show-all			= --show-leak-kinds=all
source				= functions.c utils.c shaderutils.c renderutils.c matrix.c object.c projections.c 
objects				= functions.o utils.o shaderutils.o renderutils.o matrix.o object.o projections.o 
main_source			= main.c
main_object			= main.o
main_target			= main
main_executable		= ./main
option				= -Wall
compile 			= -Wall -c
build				= -Wall -o
library				= -lm -llua5.4 -lglfw -lGL -lGLU -lGLEW



help:
	@echo "Available Makefile targets:"
	@echo "  compile			- Compile your project"
	@echo "  build				- Build your project"
	@echo "  run				- Run ./main"
	@echo "  leak-test			- Leak test ./main"eh, too long.
	@echo "  full-leak-test		- Full leak test ./main"
	@echo "  clean				- Clean up ./main and other Obj files"
	@echo "  help				- Display this help message"
	@echo " "

compile:
	$(CC) $(compile) $(main_source) $(source) $(library) 

build:
	$(CC) $(build) $(main_target) $(main_object) $(objects) $(wren) $(library)

run:
	$(main_executable)

leak-test:
	$(valgrind) $(leak-check) $(main_executable)

full-leak-test:
	$(valgrind) $(leak-check) $(show-all) $(main_executable)

clean:
	rm -f *.o $(main_target) a.out
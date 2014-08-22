#Compilador
CC = gcc

#Variaveis de diretorios
LIB = ./lib
INCLUDE = ./include
SRC = ./src
OBJ = ./obj

#Opcões de compilação
LIBFLAGS = -lsierpinski -lSDL_gfx -lSDL_ttf -lSDL
FLAGS = -Wall -Wextra -pedantic -g

limpeza: principal
	@rm lib/*.a
	@rm obj/*.o

#Cria um biblioteca dinamica com as bibliotecas
principal: biblioteca
	@$(CC) $(SRC)/main.c $(FLAGS) -I$(INCLUDE) -L$(LIB) $(LIBFLAGS) -o Sierpinski

#Compila as bibliotecas	
biblioteca:
	@$(CC) -c $(SRC)/*.c $(FLAGS) -I$(INCLUDE)
	@mv *.o obj/
	@ar -cru $(LIB)/libsierpinski.a $(OBJ)/*.o



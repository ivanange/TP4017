CFLAGS= -g3 -c -Wall
CC= gcc
SRC = src
HSRC = $(SRC)/headers
LIB = lib
OBJ = obj
BIN = bin
OBJECTS= $(OBJ)/data_structures.o $(OBJ)/utils.o $(OBJ)/main.o
HEADERS= $(HSRC)/data_structures.h $(HSRC)/main.h $(HSRC)/utils.h $(HSRC)/vars.h

do : app

$(OBJ)/data_structures.o: $(SRC)/data_structures.c
	$(CC) $(CFLAGS) $(SRC)/data_structures.c  -o $(OBJ)/data_structures.o

$(OBJ)/utils.o: $(SRC)/utils.c $(HEADERS)
	$(CC) $(CFLAGS) $(SRC)/utils.c  -o $(OBJ)/utils.o

$(OBJ)/main.o: $(SRC)/main.c $(HEADERS)
	$(CC) $(CFLAGS) $(SRC)/main.c  -o $(OBJ)/main.o


app: ${OBJECTS} 
	$(CC) -o $(BIN)/app ${OBJECTS}

clean: 
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/*

empty: 
	del /F /Q $(OBJ)\*
	del /F /Q $(BIN)\*

run: app
	./$(BIN)/app

CFLAGS= -g3 -c -Wall
CC= gcc
SRC = src
LIB = lib
OBJ = obj
BIN = bin
OBJECTS=$(OBJ)/utils.o 
MAINOBJECTS= $(OBJ)/main.o
HEADER= $(SRC)/utils.h

do : app

$(OBJ)/utils.o: $(SRC)/utils.c
	$(CC) $(CFLAGS) $(SRC)/utils.c  -o $(OBJ)/utils.o

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c -o $(OBJ)/main.o

app: ${OBJECTS} ${MAINOBJECTS}
	$(CC) -o $(BIN)/app.exe ${OBJECTS} ${MAINOBJECTS}

clean: 
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/app.exe

empty: 
	del /F /Q $(OBJ)\*
	del /F /Q $(BIN)\app.exe

run: app
	./$(BIN)/app.exe
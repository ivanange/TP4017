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

$(OBJ)/kruskal.o: $(SRC)/kruskal.c
	$(CC) $(CFLAGS) $(SRC)/kruskal.c -o $(OBJ)/kruskal.o

app: ${OBJECTS} ${MAINOBJECTS}
	$(CC) -o $(BIN)/app.exe ${OBJECTS} ${MAINOBJECTS}

kruskal: ${OBJECTS} $(OBJ)/kruskal.o
	$(CC) -o $(BIN)/kruskal.exe ${OBJECTS} $(OBJ)/kruskal.o

clean: 
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/*.exe

empty: 
	del /F /Q $(OBJ)\*
	del /F /Q $(BIN)\*.exe

run: app kruskal
	./$(BIN)/app.exe

run-kruskal: kruskal
	./$(BIN)/kruskal.exe
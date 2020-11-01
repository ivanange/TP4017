CFLAGS= -g3 -c -Wall
CC= gcc
SRC = src
LIB = lib
OBJ = obj
BIN = bin
OBJECTS=$(OBJ)/utils.o 
HEADER= $(SRC)/utils.h

do : app

$(OBJ)/utils.o: $(SRC)/utils.c
	$(CC) $(CFLAGS) $(SRC)/utils.c  -o $(OBJ)/utils.o

$(OBJ)/kruskal.o: $(SRC)/kruskal.c
	$(CC) $(CFLAGS) $(SRC)/kruskal.c -o $(OBJ)/kruskal.o

$(OBJ)/prim.o: $(SRC)/prim.c
	$(CC) $(CFLAGS) $(SRC)/prim.c -o $(OBJ)/prim.o

$(OBJ)/djikstra.o: $(SRC)/djikstra.c
	$(CC) $(CFLAGS) $(SRC)/djikstra.c -o $(OBJ)/djikstra.o

app: kruskal prim djikstra

kruskal: ${OBJECTS} $(OBJ)/kruskal.o
	$(CC) -o $(BIN)/kruskal.exe ${OBJECTS} $(OBJ)/kruskal.o

prim: ${OBJECTS} $(OBJ)/prim.o
	$(CC) -o $(BIN)/prim.exe ${OBJECTS} $(OBJ)/prim.o

djikstra: ${OBJECTS} $(OBJ)/djikstra.o
	$(CC) -o $(BIN)/djikstra.exe ${OBJECTS} $(OBJ)/djikstra.o

clean: 
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/*.exe

empty: 
	del /F /Q $(OBJ)\*
	del /F /Q $(BIN)\*.exe

run-kruskal: kruskal
	./$(BIN)/kruskal.exe

run-prim: prim
	./$(BIN)/prim.exe

run-djikstra: djikstra
	./$(BIN)/djikstra.exe
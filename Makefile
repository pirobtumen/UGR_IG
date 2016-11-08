# fichero Makefile
#

# Directorios

SRC = ./src
BIN = ./bin
INC = ./inc
OBJ = ./obj

# nombre del fichero ejecutable
#
TARGETS= practica

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I. -I$(INC)
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I. -I$(INC)

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : $(BIN)/$(TARGETS)

# regla de ejecucion
$(BIN)/$(TARGETS) : $(OBJ)/main.o $(OBJ)/revolutionsurface.o $(OBJ)/cube.o $(OBJ)/object3d.o $(OBJ)/polyhedron.o $(OBJ)/tetrahedron.o $(OBJ)/file_ply_stl.o $(OBJ)/utilities.o $(OBJ)/sphere.o $(OBJ)/reguladorwatt.o  $(OBJ)/base.o
	$(CC) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

$(OBJ)/%.o : $(SRC)/%.cc
	$(CC) -c -o $@ $(CXXFLAGS) $<

$(OBJ)/%.o : $(SRC)/%.cpp
	$(CC) -c -o $@ $(CXXFLAGS) $<

#
#
clean:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

#
#
redo:
	touch $(SRC)/*.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*
	tar -zcvf $(TARGETS).tgz *

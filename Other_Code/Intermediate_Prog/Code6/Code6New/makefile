#Rudy Orozco 1001864902 Coding Assignment 6

SRC1 = Code6_1001864902.c
SRC2 = ListLib.c
SRC3 = FileLib.c
SRC4 = DrawTool.c

OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)
OBJ4 = $(SRC4:.c=.o)

EXE = $(SRC1:.c=.e)

CFLAGS = -g

all : $(EXE)
 
$(EXE): $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)
	gcc $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) -o $(EXE) 

$(OBJ1) : $(SRC1)
	gcc -c $(CFLAGS) $(SRC1)

$(OBJ2) : $(SRC2)
	gcc -c $(CFLAGS) $(SRC2)

$(OBJ3) : $(SRC3)
	gcc -c $(CFLAGS) $(SRC3)

$(OBJ4) : $(SRC4)
	gcc -c $(CFLAGS) $(SRC4)
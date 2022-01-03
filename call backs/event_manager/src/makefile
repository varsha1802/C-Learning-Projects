IDR = ../include

BINS = ../bin

CC = gcc

CFGS = -I$(IDR)

_LIBS = receptionist.h employee.h participants.h
LIBS = $(patsubst %,$(IDR)/%,$(_LIBS))

_OBJ = receptionist.o employee.o main.o 
OBJ = $(patsubst %,$(BINS)/%,$(_OBJ))

$(BINS)/%.o: %.c $(LIBS)
	$(CC) -c -o $@ $< $(CFGS)

$(BINS)/main: $(OBJ)
	$(CC) -o $@ $^ $(CFGS) 


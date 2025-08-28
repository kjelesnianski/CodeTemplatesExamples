#### MAKEFILE

CC = g++
CFLAGS = -g

INC = ./
objects = 

all: writeVariant

app: $(objects)
	$(CC) $^ -o app -I$(INC)

writeVariant: writeVariant.cpp
	$(CC) $^ -o $@

clean:
	rm -f writeVariant 
	rm -f *.o *.bin

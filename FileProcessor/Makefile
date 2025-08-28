#### MAKEFILE

CC = g++
CFLAGS = -g

INC = ./
objects = FileProcessor_cj.o main.o

all: app binaryGenerator

app: $(objects)
	$(CC) $^ -o app -I$(INC)

binaryGenerator: binaryFileGenerate.cpp 
	$(CC) $^ -o $@

FileProcessor_cj.o: FileProcessor_cj.cpp
	$(CC) -c $^ -o $@ -I$(INC)

main.o: main.cpp
	$(CC) -c $^ -o $@ -I$(INC)

clean:
	rm -f app binaryGenerator
	rm -f *.o *.bin

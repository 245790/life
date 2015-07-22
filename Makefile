FLAGS = -Wall
CC = g++
CFLAGS = $(FLAGS) -std=c++11
LIBS =  -lglut -lGL

life: life.o grid.o cell.o
	$(CC) $(CFLAGS) -o life life.o grid.o cell.o $(LIBS)

.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) $(CFLAGS) $(LIBS) -c $<

clean:
	rm -rf *.o life

############################# Makefile ##########################
all: metro
metro: dijkstra.o main.o
	gcc -o dijkstra dijkstra.o main.o
dijstra.o: dijkstra.c header.h
	gcc -c dijkstra.c
main.o: main.c header.h
	gcc -c main.c
clean:
	rm -rf *.o dijkstra

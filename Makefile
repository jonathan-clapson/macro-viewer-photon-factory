CC 		= gcc
CFLAGS 	= -O3
RM		= rm -f

all: viewer

gnuplot_i.o: gnuplot_i.c gnuplot_i.h
	$(CC) $(CFLAGS) -c -o gnuplot_i.o gnuplot_i.c
	
main.o: main.c
	$(CC) -c -o main.o main.c
	
viewer: gnuplot_i.o main.o
	$(CC) -o viewer main.c gnuplot_i.c
	

clean:
	$(RM) gnuplot_i.o


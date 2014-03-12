CC 		= gcc
CFLAGS 	= -O3
RM		= rm -f

all: viewer

viewer: gnuplot_i.c main.c
	$(CC) $(CFLAGS) -o viewer main.c gnuplot_i.c
	

clean:
	$(RM) viewer


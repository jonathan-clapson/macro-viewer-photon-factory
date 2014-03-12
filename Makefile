CC 		= g++
CFLAGS 	= -O3
RM		= rm -f

all: viewer

viewer: gnuplot_i.cpp main.cpp shape_math.cpp
	$(CC) $(CFLAGS) -o viewer main.cpp gnuplot_i.cpp shape_math.cpp
	

clean: clean_tmp
	$(RM) viewer

clean_tmp:
	$(RM) gnuplot_tmpdatafile_*

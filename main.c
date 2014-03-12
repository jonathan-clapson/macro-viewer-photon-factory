#include <stdio.h>
#include <unistd.h>

#include "gnuplot_i.h"

#define LIST_SIZE 500

double x_set[LIST_SIZE];
double y_set[LIST_SIZE];
int point_counter = 0;

void add_point(double x, double y)
{
	if (point_counter >= LIST_SIZE) {
		printf("list not big enough\n");
		return;
	}
	
	x_set[point_counter] = x;
	y_set[point_counter] = y;
	point_counter ++;
}

int parseFile(FILE *fp)
{
	//fscanf(fp, "%f %f %f\n");
	
	
	return 0;
}

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	
	gnuplot_ctrl *gnu_plot = gnuplot_init();
	if (argc != 2) {
		printf("only arg is file name\n");
		return -1;
	}
	fp = fopen(argv[1], "r");
	if (!fp) {
		fprintf(stderr, "failed to open file %s\n", argv[1]);
		return -1;
	}
	
	parseFile(fp);	
	
	add_point(5.00, 2.00);
	
	gnuplot_plot_xy(gnu_plot, x_set, y_set, point_counter, "display");
	
	fclose(fp);
	
	while(1);
	
	gnuplot_close(gnu_plot);	
	
	return 0;
}

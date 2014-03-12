#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <unistd.h>

#include "gnuplot_i.h"
#include "shape_math.h"

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

void get_file_item(FILE *fp, char *buffer, int buflen) {
	int i;
	for (i=0; i<buflen-1; i++) {
			int c = fgetc(fp);
			if ( (c == ';') || (c == ',') || (c == '\n') || feof(fp) ) {
				break;
			}			
			buffer[i] = c;
			if (c == '\r') i--;
	}	
	buffer[i] = '\0';
}

void clear_line(FILE *fp) {
	int c = 0;
	while (c != '\n') {
		c = fgetc(fp);
	}	
}

int parseFile(FILE *fp)
{
	char buffer[200];
	
	while (!feof(fp)) {
		get_file_item(fp, buffer, sizeof(buffer));
		if (strcmp(buffer, "comment")==0)
			continue;
		else if (strcmp(buffer, "LINE") == 0) {
			point_t result;
			point_t start;
			double t = 0.01;
			get_file_item(fp, buffer, sizeof(buffer));
			start.x = atof(buffer);
			get_file_item(fp, buffer, sizeof(buffer));
			start.y = atof(buffer);
			
			point_t end;
			get_file_item(fp, buffer, sizeof(buffer));
			end.x = atof(buffer);
			get_file_item(fp, buffer, sizeof(buffer));
			end.y = atof(buffer);			
			
			line_get_x_y( result, start, end, t);
		}
		printf("command: %s\n", buffer);
		
	}	
	
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

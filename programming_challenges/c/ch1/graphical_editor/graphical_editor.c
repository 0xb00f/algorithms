#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* definitions */

#define SCREENMAX 250
#define LINEMAX 20
#define ARGMAX 10
#define ARGINT 1
#define ARGCHAR 2

union value {
	
	char chr;
	int num;

};

typedef struct arg_vec {

	union value data;
	int type;

} arg_vec;

/* global 2D screen array and dimensions */

char screen[SCREENMAX+1][SCREENMAX+1];
int rowmax = 0, colmax = 0;

/* helper functions */

void terminate(void)
{

	exit(0);

}

void colour_pixel(int row, int col, char colour)
{
  
	if(row < 0 || col < 0 || row > SCREENMAX || col > SCREENMAX) return; 	
	screen[row][col] = colour;

}

void order_args(int* start, int* end)
{

	if(*start > *end)
	{
	
		int tmp = *start;
		*start = *end;
		*end = tmp;

	}

}

void draw_vert_segment(int col, int start, int end, char colour)
{
	
	order_args(&start,&end);

	int i;
	for(i=start; i <= end; i++)
	{

		colour_pixel(i,col,colour);

	}

}

void draw_horz_segment(int row, int start, int end, char colour)
{
	
	order_args(&start,&end);
	int i;
	for(i=start; i <= end; i++)
	{
		
		colour_pixel(row,i,colour);

	}

}

void draw_rectangle(int row1, int col1, int row2, int col2, char colour) /*make sure args right*/
{

	int i;
	for(i=row1; i <= row2; i++)
	{

		draw_horz_segment(i,col1,col2,colour);

	}

}

void init_screen(int rows, int cols)
{
	
	int i,j;
	for(i=0; i <= rows; i++)
	{

		for(j=0; j <= cols; j++)
		{

			colour_pixel(i,j,'O');

		}

	}

}

void clear_screen(void)
{

	init_screen(rowmax,colmax);

}

void fill_region(int row, int col, char colour, char region)
{
	
	if(row <= 0 || col <= 0 || row > rowmax || col > colmax) return;
	if(screen[row][col] != region) return;

	colour_pixel(row,col,colour);

	if(screen[row+1][col] != colour)
	{

		fill_region(row+1,col,colour,region);
	
	}
	
	if(screen[row-1][col] != colour)
	{

		fill_region(row-1,col,colour,region); 

	}
	
	if(screen[row][col+1] != colour)
	{

		fill_region(row,col+1,colour,region);
	
	}
	
	if(screen[row][col-1] != colour)
	{

		fill_region(row,col-1,colour,region);

	}

}

int extract_args(char input[LINEMAX], arg_vec args[ARGMAX])
{

	char* token = strtok(input," ");
	int j = 0;
	
	while(token != NULL)
	{
		
		arg_vec a;

		if(isdigit(*token))
		{
			
			a.data.num = atoi(token);
			a.type = ARGINT;
			args[j++] = a;
	
		}
		else if(isalpha(*token))
		{
			
			a.data.chr = *token;
			a.type = ARGCHAR;
			args[j++] = a;

		}

		token = strtok(NULL," ");
		
	}

	return j;

}

void write_file(char* filename)
{

	printf("%s",filename);

	int i,j;
	for(i=1; i <= rowmax; i++)
	{

		for(j=1; j <= colmax; j++)
		{

			putchar(screen[i][j]);

		}

		putchar('\n');

	}

}

void parse_instruction(char instr[LINEMAX])
{
	
	arg_vec args[ARGMAX];
	int num_args = extract_args(instr,args);
	char region = '\0';

	switch(instr[0])
	{

	case 'I':

	        rowmax = args[2].data.num > SCREENMAX ? SCREENMAX : args[2].data.num;
	        colmax = args[1].data.num > SCREENMAX ? SCREENMAX : args[1].data.num;
		init_screen(rowmax, colmax);
		break;
	
	case 'C':

	        clear_screen();
		break;

	case 'L':
		
		colour_pixel(args[2].data.num,
			     args[1].data.num,
			     args[3].data.chr);
		break;

	case 'V':
		
		draw_vert_segment(args[1].data.num,
				  args[2].data.num,
				  args[3].data.num,
				  args[4].data.chr);
		break;

	case 'H':
		

		draw_horz_segment(args[3].data.num,
				  args[1].data.num,
				  args[2].data.num,
				  args[4].data.chr);
		break;

	case 'K':
		

		draw_rectangle(args[2].data.num,
			       args[1].data.num,
			       args[4].data.num,
			       args[3].data.num,
			       args[5].data.chr);
		break;

	case 'F':
		
	        region = screen[args[2].data.num][args[1].data.num]; /* do error checking */
		fill_region(args[2].data.num,
			    args[1].data.num,
			    args[3].data.chr,
			    region);
		break;

	case 'S':
		
		write_file(instr+2);
		break;

	case 'X':

		terminate();

	default:
	
		return;

	}

}

int main(void) 
{

	char input[LINEMAX] = {'\0'};
	

	while(1)
	{

		fgets(input,LINEMAX,stdin);
		parse_instruction(input);
		
	}

	return 0;	

}

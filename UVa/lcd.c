#include <stdio.h>
#include <stdlib.h>

#define small_dash_line        0
#define left_single_bar_line   1
#define right_single_bar_line  2
#define double_bar_line        3
#define empty_line             4

#define MIN_ROWS 5
#define MIN_COLS 3

int line_type(char* line) {

  /*determine which type of line we're dealing with*/

  if(line[1] == '-') {

    return small_dash_line;
    
  }else if(line[0] == '|' && line[2] == '|') {

    return double_bar_line;

  }else if(line[0] == '|' && line[2] == ' ') {

    return left_single_bar_line;
    
  }else if(line[0] == ' ' && line[2] == '|') {

    return right_single_bar_line;

  }else{

    return empty_line;

  }

}


void fill_line(char* arr, char c, int start, int end) {

  /*fill in the line with the desired character*/
  
  int i;
  for(i = start; i < end; i++) {

    arr[i] = c;

  }

}

char* scale_line(int cols, char* original, char* new) {

  /*scale line dependent on type to the required width*/

  int i;

  switch(line_type(original)) {

     case small_dash_line:

        new[0] = ' ';
	new[cols-1] = ' ';

        for(i = 1; i < cols-1; i++) { /*make these into fill_line()*/

	  new[i] = '-';

        }

        break;

      case left_single_bar_line:

	new[0] = '|';

	for(i = 1; i < cols; i++) {

	  new[i] = ' ';

	}

	break;

     case right_single_bar_line:

       new[cols-1] = '|';

       for(i = 0; i < cols-1; i++) {

	 new[i] = ' ';

       }

       break;

     case double_bar_line:

       new[0] = '|';
       new[cols-1] = '|';

       for(i = 1; i < cols-1; i++) {

	 new[i] = ' ';

       }

       break;

     case empty_line:
       

       for(i = 0; i < cols; i++) {

	 new[i] = ' ';

       }

       break;
  }

  return new;

}

char** scale_digit(int rows, int cols, char digit[MIN_ROWS][MIN_COLS]) {

  /*scale digit to required dimensions*/

  char** arr = (char**)malloc(rows*sizeof(char*));
  int i, j;

  for(i = 0; i < rows; i++) {

    arr[i] = (char*)malloc((cols+1)*sizeof(char));

  }
  
  int dim = cols - 2;
  int line = 0;
  for(i = 0; i < 5; i++) {

    switch(line_type(digit[i])) {

       case empty_line:

       case small_dash_line:

	 arr[line] = scale_line(cols,digit[i],arr[line]);
	 line++;
	 break;

       default:

	 j = 0;
	 while(j < dim) {

	   arr[line] = scale_line(cols,digit[i],arr[line]);
	   j++;
	   line++;
	
	 }

    }

  }
  
  return arr;
    
}

int main(void) {

  /*variables for dimension & looping*/
  int dim,i,j,k;
  
  /*3D array that maps ints to their LCD repr*/
  char digits[10][MIN_ROWS][MIN_COLS] = {{" - ","| |","   ","| |"," - "}, /*zero*/
					 {"   ","  |","   ","  |","   "}, /*one*/
					 {" - ","  |"," - ","|  "," - "}, /*two*/
					 {" - ","  |"," - ","  |"," - "}, /*three*/
					 {"   ","| |"," - ","  |","   "}, /*four*/
					 {" - ","|  "," - ","  |"," - "}, /*five*/
					 {" - ","|  "," - ","| |"," - "}, /*six*/
					 {" - ","  |","   ","  |","   "}, /*seven*/
					 {" - ","| |"," - ","| |"," - "}, /*eight*/
					 {" - ","| |"," - ","  |"," - "}}; /*nine*/

  /*main loop*/
  while(1) {

    /*string to hold input number to be printed*/
    char num_str[9] = {'\0'};

    /*scan input*/
    scanf("%d %s",&dim,num_str);
        
    /*break if dimension is zero*/
    if(dim == 0) {

      break;

    }

    /*convert string to int array*/
    int num_arr[9] = {0};
    int len = 0;
    i = 0;
    while(num_str[i] != '\0') {

      num_arr[i] = num_str[i] - '0';
      i++;
      len++;

    }

    /*compute dimensions and initialise output buffer*/
    int rows = 2*dim + 3;
    int cols = dim + 2;
    char **output = malloc(rows*sizeof(int*));

    for(i = 0; i < rows; i++) {

      output[i] = malloc((len-1)+len*cols*sizeof(char));

      for(k = 0; k < (len-1)+len*cols; k++) {

	output[i][k] = ' ';

      }

    }

    /*convert each digit in the input into it's scaled ascii repr and add to buffer*/
    int start_pos = 0;
    for(i = 0; i < len; i++) {

      char **digit = scale_digit(rows,cols,digits[ num_arr[i] ]);

      for(j = 0; j < rows; j++) {

	for(k = 0; k < cols; k++) {

	  output[j][start_pos+k] = digit[j][k];

	}

      }

      /*free digit memory*/
      for(j = 0; j < rows; j++) {

	  free(digit[j]);

      }

      free(digit);
      
      start_pos += cols+1;

    }

    /*print output*/
    for(i = 0; i < rows; i++) {

      for(j = 0; j < (len-1)+len*cols; j++) {

	printf("%c",output[i][j]);

      }

      printf("\n");

    }

    /*free output memory*/
    for(i = 0; i < rows; i++) {

      free(output[i]);

    }

    free(output);
    
    printf("\n");
      
  }

  return 0;

}

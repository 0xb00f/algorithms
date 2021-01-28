#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*accepted but need to fix memory leaks*/

#define DEBUG 0

#define RAMSIZE  1000
#define REGMAX   10
#define INSTRMAX 3

int **ram;
int *regs;
int pc;

void init(void) {

  int i, j;

  ram = (int**)malloc(RAMSIZE*sizeof(int*));
  for(i = 0; i < RAMSIZE; i++) {

    ram[i] = (int*)malloc(INSTRMAX*sizeof(int));

    for(j = 0; j < INSTRMAX; j++) {

      ram[i][j] = 0;

    }

  }

  regs = (int*)malloc(REGMAX*sizeof(int));
  for(i = 0; i < REGMAX; i++) {

    regs[i] = 0;

  }

}

void clear(void) {

  int i, j;

  for(i = 0; i < RAMSIZE; i++) {

    for(j = 0; j < INSTRMAX; j++) {
      
      ram[i][j] = 0;
      
    }
    
  }

  for(i = 0; i < REGMAX; i++) {

      regs[i] = 0;

  }

  pc = 0;

}

int* parse_instruction(char *line) {

  int *arr = malloc(INSTRMAX*sizeof(int));
  int i;

  for(i = 0; i < INSTRMAX; i++) {

    arr[i] = line[i] - '0';

  }

  return arr;

}

void set_reg_from_ram(int args[INSTRMAX]) {

  /*get address from register*/
  int addr = regs[ args[2] ];

  /*extract the value from RAM at addr*/
  int value = 100*ram[addr][0] + 10*ram[addr][1] + ram[addr][2];
  value %= RAMSIZE;

  /*set target register to value from RAM*/
  regs[ args[1] ] = value;
  
}

void set_ram_from_reg(int args[INSTRMAX]) {

  /*extract addr from register*/
  int addr = regs[ args[2] ];

  /*extract value from register*/
  int value = regs[ args[1] ];

  /*write value into ram*/
  int i = 2;
  while(i > -1) {

    ram[addr][i] = value % 10;
    value /= 10;
    i--;

  }

}

void execute_instruction(int args[INSTRMAX]) {

  switch(args[0]) {

  case 1:

    break;

  case 2:

    regs[ args[1] ] = args[2];
    break;

  case 3:

    regs[ args[1] ] += args[2];
    regs[ args[1] ] %= RAMSIZE;
    break;

  case 4:

    regs[ args[1] ] *= args[2];
    regs[ args[1] ] %= RAMSIZE;
    break;

  case 5:

    regs[ args[1] ] = regs[ args[2] ];
    break;

  case 6:

    regs[ args[1] ] += regs[ args[2] ];
    regs[ args[1] ] %= RAMSIZE;
    break;

  case 7:

    regs[ args[1] ] *= regs[ args[2] ];
    regs[ args[1] ] %= RAMSIZE;
    break;

  case 8:

    set_reg_from_ram(args);
    break;

  case 9:

    set_ram_from_reg(args);
    break;

  case 0:

    if(regs[args[2]] != 0) {

      pc = regs[args[1]];
      return;

    }

  }

  pc++;

}


void read_program(void) {

  int index = 0;

  while(index < RAMSIZE) {

    char input[10] = {'\0'};

    /*get instruction*/
    fgets(input,10,stdin);

    /*exit at end*/
    if(input[0] == '\n') {

      break;

    }

    /*parse instruction*/
    int *args = parse_instruction(input);
    
    /*save to ram*/
    ram[index] = args;

    index++;
    
  }

}

int halt(int ram[3]) {

  return ram[0] == 1 && ram[1] == 0 && ram[2] == 0;

}

int execute_program(void) {

  int count = 1;
  
  pc = 0;

  while(1) {

    execute_instruction(ram[pc]);
    count++;

    if(halt(ram[pc])) return count;
    
  }

}

int main(void) {

  int i, n;

  scanf(" %d",&n);

  /*consume trailing newlines*/
  getchar();
  getchar();

  init();
  
  for(i = 0; i < n; i++) {

    clear();

    read_program();

    int result = execute_program();

    printf("%d\n",result);
    
    if(i < n-1) printf("\n");

  }
  
  return 0;

}

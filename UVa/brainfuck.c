#include <stdio.h>
#include <string.h>

#define MEMMAX 100
#define LINEMAX 100000+2

unsigned char memory[MEMMAX] = {0};
int pointer = 0;

void reset(void)
{

	pointer = 0;
	int i;
	for(i=0; i<MEMMAX; i++) memory[i] = 0;

}

void inc_ptr(void)
{

	pointer = (pointer+1) % MEMMAX;

}

void dec_ptr(void)
{

	if(pointer == 0) 
	{

		pointer = MEMMAX-1;

	}
	else
	{

		pointer--;

	}

}

void inc_byte(void)
{

	memory[pointer]++;

}

void dec_byte(void)
{

	memory[pointer]--;

}


void dump_memory(int n)
{
	
	printf("Case %d: ",n);
	int i;
	for(i=0; i < MEMMAX; i++)
	{

		printf("%02hhX",memory[i]);
		if(i < MEMMAX-1) printf(" ");

	}
	printf("\n");

}

void perform_brainfuck_instr(char instr)
{
	switch(instr)
	{
		case '>':		
			inc_ptr();
			break;
		case '<':
			dec_ptr();
			break;
		case '+':
			inc_byte();
			break;
		case '-':
			dec_byte();
			break;
		default:
			return;
	}
}

int main(void)
{
	char line[LINEMAX] = {0};
	int case_n, num_cases;
	
	scanf("%d",&num_cases);
	getchar(); /*consume trailing newline*/
	
	for(case_n=1; case_n <= num_cases; case_n++)
	{	
	  fgets(line,LINEMAX,stdin);
	  int i;
	  for(i = 0; line[i] != '\n'; i++)
	    {	      
	      perform_brainfuck_instr(line[i]);			
	    }
	  dump_memory(case_n);
	  reset();
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NCARDS  52
#define NSUITS  4
#define NVALUES 13
#define BUFMAX  500
#define SHUFMAX 1000

const char *suits[] = {"Clubs","Diamonds","Hearts","Spades"};
const char *values[] = {"2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};
int *cards;
int *shuf_seq;
int **shuffles;
int num_shufs;

void init_data(void) {

  cards = calloc(NCARDS+2,sizeof(int));
  shuf_seq = malloc((SHUFMAX+2)*sizeof(int));

  int i;
  for(i = 0; i < SHUFMAX+2; i++) {

    shuf_seq[i] = -1;

  }

  for(i = 0; i < NCARDS; i++) {

    cards[i] = i;

  }

}

void clear_data(void) {

  int i;
  for(i = 0; i < NCARDS; i++) {

    cards[i] = i;

  }

  for(i = 0; i < SHUFMAX; i++) {

    shuf_seq[i] = -1;

  }

  for(i = 0; i < num_shufs+2; i++) {

    free(shuffles[i]);

  }

  free(shuffles);
  num_shufs = 0;

}

char* int_to_card(int n) {

  int value = n % NVALUES;
  int suit = n / NVALUES;

  char *str = malloc(50*sizeof(char));

  sprintf(str,"%s of %s",values[value],suits[suit]);

  return str;

}

void print_deck(void) {

  int i;
  for(i = 0; i < NCARDS; i++) {

    printf("%s\n",int_to_card(cards[i]));

  }
 
}

void print_cards(void) {

  printf("Cards are: ");
  
  int i;
  for(i = 0; i < NCARDS; i++) {

    printf("%d ",cards[i]);

  }

  printf("\n");
  
}

void apply_shuffle(int index) {

  int i;

  int *arr = calloc(NCARDS+2,sizeof(int));

  /*probs more efficient way of doing this in-place*/
  for(i = 0; i < NCARDS; i++) {

    arr[i] = cards[ shuffles[index][i] ];
    
  }

  for(i = 0; i < NCARDS; i++) {

    cards[i] = arr[i];

  }
  
  free(arr);
  
}

void transform_deck(void) {

  int i;
  for(i = 0; i < SHUFMAX; i++) {

    if(shuf_seq[i] < 0) {

      return;

    }

    apply_shuffle(shuf_seq[i]);

  }

}

void add_shuffle(char *line, int index) {

  shuffles[index] = malloc((NCARDS+2)*sizeof(int));

  const char delim[2] = " ";
  char *token = strtok(line,delim);
  int i = 0;

  while(token != NULL && i < NCARDS) {

    shuffles[index][i] = (int)strtol(token,(char**)NULL,10) - 1;
    token = strtok(NULL,delim);
    i++;

  }

  assert(i == NCARDS);

}

int read_input(void) {

  char buf[BUFMAX];
  int i;

  /*get number of shuffles*/
  if(fgets(buf,BUFMAX,stdin) != NULL) {

    num_shufs = (int)strtol(buf,(char**)NULL,10);
    shuffles = (int**)malloc((num_shufs+2)*sizeof(int*));

  }else{

    printf("input exiting - num_shufs\n");
    return 0;

  }
  
  /*read in each of the shuffles*/
  for(i = 0; i < num_shufs; i++) {

    if(fgets(buf,BUFMAX,stdin) == NULL) {

      printf("input exiitng - read in shuffle %d\n",i);
      return 0;

    }

    add_shuffle(buf,i);

  }
  
  /*read in the sequence of shuffles applied*/
  i = 0;
  while(buf[0] != '\n' && i < SHUFMAX) {

    if(fgets(buf,BUFMAX,stdin) == NULL) {

      return 1;

    }

    shuf_seq[i] = (int)strtol(buf,(char**)NULL,10) - 1;
    i++;

  }

  return 1;

}

int main(void) {

  char line[BUFMAX];
  int num_cases, i;

  init_data();

  /*read in number of cases*/
  if(fgets(line,BUFMAX,stdin) == NULL) {

    printf("exiting - cases\n");
    return 1;

  }

  num_cases = (int)strtol(line,(char**)NULL,10);

  /*consume trailing newline*/
  fgets(line,BUFMAX,stdin);
  
  /*for each case determine the hand that results*/
  for(i = 0; i < num_cases; i++) {

    /*
    if(!read_input()) {

      printf("exiting - input\n");
      return 1;

      }*/
    read_input();

    transform_deck();
    print_deck();
    clear_data();

    if( i < num_cases-1 ) {
      
      printf("\n");

    }

  }
  
  return 0;

}

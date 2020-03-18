#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*tiebreaking for lowest three hands*/
#define DEBUG      0
#define WHITE      1
#define BLACK      2
#define HANDSIZE   5
#define NCARDS     52
#define NSUITS     4
#define LINEMAX    50
#define HIGH_CARD  100
#define PAIR       200
#define TWO_PAIR   300
#define THREE_KIND 400
#define STRAIGHT   500
#define FLUSH      600
#define FULL_HOUSE 700
#define FOUR_KIND  800
#define STR_FLUSH  900

/*globals*/
char values[] = "23456789TJQKA";
char suits[] = "CDHS";
int white_hand[HANDSIZE];
int black_hand[HANDSIZE];
int white_value_count[NCARDS/NSUITS];
int white_suit_count[NSUITS];
int black_value_count[NCARDS/NSUITS];
int black_suit_count[NSUITS];
int white_value_stats[6];
int white_suit_stats[6];
int black_value_stats[6];
int black_suit_stats[6];

/*queue stuff*/

typedef struct Qnode Qnode;

struct Qnode {
  
  int data;
  Qnode *next;

};

typedef struct {

  Qnode *head;
  int size;

} Queue;

void print_queue(Queue *q) {

  Qnode *curr = q->head;

  printf("queue holds: ");

  while(curr) {

    printf("%d ",curr->data);
    curr = curr->next;

  }

  printf("\n");

}

Queue *create_queue(void) {

  Queue *q = malloc(sizeof(Queue));

  if(!q) {

    return NULL;

  }

  q->head = NULL;
  q->size = 0;

  return q;

}

Qnode * makeNode( int data )
{
   Qnode *new_node =(Qnode *)malloc( sizeof( Qnode ));
   if( new_node == NULL ) {
      fprintf(stderr,"Error: memory allocation failed.\n");
      exit( 1 );
   }
   new_node->data = data;
   new_node->next = NULL;
   return( new_node );
}

int *stack_pop( Queue *q ) {

  if(q->head != NULL) {

    int val = q->head->data;
    int *val_p = &val;
    Qnode *tmp;
    
    tmp = q->head;
    q->head = q->head->next;
    free(tmp);

    q->size--;

    return val_p;

  }else{

    return NULL;

  }
  
}

int *dequeue( Queue *q ) {

  return stack_pop(q);

}

int is_empty( Queue *q ) {

  return q->size == 0;

}

void insert_in_order(Queue *q,int value) {

  Qnode *curr = q->head;

  /*empty queue*/
  if(curr == NULL) {

    q->head = makeNode(value);
    q->size++;
    return;

  }

  /*head of queue greater than value*/
  if(curr->data > value) {

    Qnode *new = makeNode(value);

    new->next = q->head;
    q->head = new;
    q->size++;
    return;

  }

  /*value sits somewhere in the middle or the end*/
  while(curr->data < value && curr->next != NULL && curr->next->data < value) {

    curr = curr->next;

  }

  Qnode *new = makeNode(value);

  new->next = curr->next;
  curr->next = new;
  q->size++;
  
}


int dequeue_end(Queue *q) {

  Qnode *curr = q->head, *prev = curr;

  /*empty queue*/
  if(curr == NULL) {

    return -1;

  }

  /*single item queue*/
  if(q->size == 1) {

    int result = curr->data;
    free(curr);
    q->head = NULL;
    q->size--;

    return result;

  }

  while(curr->next) {

    curr = curr->next;

  }

  while(prev->next != curr) {

    prev = prev->next;

  }

  int result = curr->data;
  free(curr);
  prev->next = NULL;
  q->size--;

  return result;

}

/*poker hand functions*/

int rank_card(char value, char suit) {

  int i, j;

  for(i = 0; i < (NCARDS/NSUITS); i++) {

    if(values[i] == value) {

      for(j = 0; j < NSUITS; j++) {

	if(suits[j] == suit) {

	  return i*NSUITS + j;

	}

      }

    }

  }

  printf("rank: bad input: value = %c, suit = %c\n",value,suit);
  return -1;

}

char suit(int card) {

  return suits[card % NSUITS];

}

char value(int card) {

  return values[ card/NSUITS ];

}

void clear_data(void) {

  int i;

  for(i = 0; i < HANDSIZE; i++) {

    white_hand[i] = -1;
    black_hand[i] = -1;

  }

  for(i = 0; i < (NCARDS/NSUITS); i++) {

    white_value_count[i] = 0;
    black_value_count[i] = 0;

  }

  for(i = 0; i < NSUITS; i++) {

    white_suit_count[i] = 0;
    black_suit_count[i] = 0;

  }

}

void clear_stats(int value_stats[6],int suit_stats[6]) {

  int i;

  for(i = 0; i < 6; i++) {

    value_stats[i] = 0;
    suit_stats[i] = 0;

  }

}

void parse_input(char line[LINEMAX]) {

  const char delim[2] = " ";

  char* token = strtok(line,delim);

  int i = 0;

  while(token != NULL && i < 10) {

    if(i < 5) {

      black_hand[i] = rank_card(token[0],token[1]);
      
    }else{

      white_hand[i-5] = rank_card(token[0],token[1]);

    }

    token = strtok(NULL,delim);
    i++;

  }

}

int read_input(void) {

  char line[LINEMAX] = {'\0'};

  if(fgets(line,LINEMAX,stdin) == NULL) {

    return 1;

  }

  parse_input(line);

  return 0;

}

int rank_hand(int hand, int high_value) {

  return hand + high_value;

}

/*function that returns the highest index in a consecutive run of 5*/
int run_of_five_values(int value_count[NCARDS/NSUITS]) {

  int i, conseq = 0;

  for(i = 0; i < (NCARDS/NSUITS); i++) {

    if(value_count[i] == 0) {

      continue;

    }

    conseq++;

    if(value_count[i+1] == 0) {

      break;

    }

  }

  return conseq == 5 ? i : 0;

}

/*function that returns the index that holds the highest nonzero count*/
int find_max(int value_count[NCARDS/NSUITS]) {

  int max = 0, i;
    for(i = 0; i < (NCARDS/NSUITS); i++) {

      if(value_count[i] > 0 && value_count[i] > max) {

	max = i;

      }

    }

    return max;

}

/*function to read in stats*/
void compile_stats(int value_count[NCARDS/NSUITS], int suit_count[NSUITS],int value_stats[6],int suit_stats[6]) {

  int i;

  for(i = 0; i < (NCARDS/NSUITS); i++) {

    if(value_count[i] > 0) {

      value_stats[ value_count[i] ]++;

    }

  }

  for(i = 0; i < NSUITS; i++) {

    if(suit_count[i] > 0) {

      suit_stats[ suit_count[i] ]++;

    }

  }

}

int check_high_hands(int value_count[NCARDS/NSUITS],int suit_count[NSUITS],int value_stats[6],int suit_stats[6]) {

  int high_card;
  
  /*clear & compile hand stats*/
  clear_stats(value_stats,suit_stats);
  compile_stats(value_count,suit_count,value_stats,suit_stats);

  /*check for each of the high hands*/

  if(suit_stats[5]) {

    /*maybe disambiguate these?*/
    
    if((high_card = run_of_five_values(value_count))) {

      /*straight flush*/
      return rank_hand(STR_FLUSH,high_card);

    }else{

      /*flush*/
      int max = 0, i;
      for(i = 0; i < (NCARDS/NSUITS); i++) {

	if(value_count[i] > 0 && i > max) {

	  max = i;

	}

      }
      return rank_hand(FLUSH,max);

    }

  }else if(value_stats[4]) {
    
    /*four of a kind*/
    int max = 0, i;
    for(i = 0; i < (NCARDS/NSUITS); i++) {

	if(value_count[i] == 4) {

	  max = i;
	  break;

	}

      }
    return rank_hand(FOUR_KIND,max);

  }else if(value_stats[3] && value_stats[2]) {
    
    /*full house*/
    for(high_card = 0; high_card < (NCARDS/NSUITS); high_card++) {

      if(value_count[high_card] == 3) {

	return rank_hand(FULL_HOUSE,high_card);
	
      }
      
    }

  }else if((high_card = run_of_five_values(value_count))) {
    
    /*straight*/
    return rank_hand(STRAIGHT,high_card);


  }else if(value_stats[3]) {
    
    /*three of a kind*/
    for(high_card = 0; high_card < (NCARDS/NSUITS); high_card++) {

      if(value_count[high_card] == 3) {

	return rank_hand(THREE_KIND,high_card);
	
      }
      
    }

  }

  return 0;
  
}

void check_low_hands(void) {

  int i;

  /*init a white & black queue*/
  Queue *black_q = create_queue();
  Queue *white_q = create_queue();
  int white_pairs = 0, black_pairs = 0;

  /*for each hand, enqueue pairs and single cards from highest to lowest*/
  for(i = 0; i < (NCARDS/NSUITS); i++) {

    /*white hand*/
    if(white_value_count[i] == 2) {

      white_pairs++;
      insert_in_order(white_q,rank_hand(PAIR,i));

    }else if(white_value_count[i] == 1) {

      insert_in_order(white_q,rank_hand(HIGH_CARD,i));

    }

    /*black hand*/
    if(black_value_count[i] == 2) {

      black_pairs++;
      insert_in_order(black_q,rank_hand(PAIR,i));

    }else if(black_value_count[i] == 1) {

      insert_in_order(black_q,rank_hand(HIGH_CARD,i));

    }

  }
  
  /*check for two pair*/
  if(white_pairs > black_pairs) {

    printf("White wins.\n");
    return;

  }else if(black_pairs > white_pairs) {

    printf("Black wins.\n");
    return;

  }

  /*dequeue values, comparing them until one is greater, or one or both queues are empty*/
  while(!is_empty(white_q) && !is_empty(black_q)) {

    int black = dequeue_end(black_q);
    int white = dequeue_end(white_q);

    if(black > white) {

      printf("Black wins.\n");
      return;

    }else if(white > black) {

      printf("White wins.\n");
      return;

    }

  }

  /*tie*/
  printf("Tie.\n");

}

int read_cards(int arr[HANDSIZE],int value_count[NCARDS/NSUITS],int suit_count[NSUITS],int value_stats[6],int suit_stats[6]) {

  int i;

  for(i = 0; i < HANDSIZE; i++) {

    value_count[ arr[i] / NSUITS ]++;
    suit_count[ arr[i] % NSUITS ]++;
    
  }

  return check_high_hands(value_count,suit_count,value_stats,suit_stats); 
					  
}

int main(void) {

  while(1) {

    /*clear data*/
    clear_data();

    /*read and parse input, exit if none*/
    int result = read_input();

    if(result) {

      break;

    }

    int white_result = read_cards(white_hand,white_value_count,white_suit_count,white_value_stats,white_suit_stats);
    int black_result = read_cards(black_hand,black_value_count,black_suit_count,black_value_stats,black_suit_stats);

    if((white_result == 0 && black_result == 0) || ((white_result > FLUSH && white_result < FULL_HOUSE) && (black_result > FLUSH && black_result < FULL_HOUSE))) {

      check_low_hands();

    }else if(white_result > black_result) {

      printf("White wins.\n");

    }else if(black_result > white_result) {

      printf("Black wins.\n");

    }else{

      printf("Tie.\n");

    }

  }

  return 0;

}

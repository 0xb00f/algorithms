#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMTEAMS 102
#define NUMPROBS 12
#define BUFMAX   100

/*queue stuff*/

typedef struct Qnode Qnode;

struct Qnode {
  
  int team;
  int score;
  int penalty;
  Qnode *next;

};

typedef struct {

  Qnode *head;
  int size;

} Queue;

Queue *create_queue(void) {

  Queue *q = malloc(sizeof(Queue));

  if(!q) {

    return NULL;

  }

  q->head = NULL;
  q->size = 0;

  return q;

}

Qnode * makeNode( int team, int score, int penalty)
{
   Qnode *new_node =(Qnode *)malloc( sizeof( Qnode ));
   if( new_node == NULL ) {
      fprintf(stderr,"Error: memory allocation failed.\n");
      exit( 1 );
   }
   new_node->team = team;
   new_node->score = score;
   new_node->penalty = penalty;
   new_node->next = NULL;
   return( new_node );
}

Qnode *stack_pop( Queue *q ) {

  if(q->head != NULL) {

    Qnode *tmp;
    
    tmp = q->head;
    q->head = q->head->next;

    q->size--;

    return tmp;

  }else{

    return NULL;

  }
  
}

Qnode *dequeue( Queue *q ) {

  return stack_pop(q);

}

int is_empty( Queue *q ) {

  return q->size == 0;

}

/*is n1 higher ranked than n2?*/
int is_higher_ranked(Qnode *n1, Qnode *n2) {

  if(n1->score > n2->score) {

    return 1;

  }else if(n1->score < n2->score) {

    return 0;

  }

  if(n1->penalty < n2->penalty) {

    return 1;

  }else if(n1->penalty > n2->penalty) {

    return 0;

  }

  if(n1->score == n2->score && n1->penalty == n2->penalty) {
    
    if(n1->team < n2->team) {

      return 1;

    }else{

      return 0;

    }

  }
    
}

/*redo*/
void insert_in_order(Queue *q,int team,int score,int penalty) {

  Qnode *curr = q->head;
  Qnode *new = makeNode(team,score,penalty);

  /*empty queue*/
  if(curr == NULL) {

    q->head = new;
    q->size++;
    return;

  }

  /*higher ranked than the current leader*/
  if(is_higher_ranked(new,curr)) {

    new->next = q->head;
    q->head = new;
    q->size++;
    return;

  }

  /*value sits somewhere in the middle or the end*/
  while(is_higher_ranked(curr,new) && curr->next != NULL && is_higher_ranked(curr->next,new)) {

    curr = curr->next;

  }

  new->next = curr->next;
  curr->next = new;
  q->size++;
  
}


Qnode *dequeue_end(Queue *q) {

  Qnode *curr = q->head, *prev = curr;

  /*empty queue*/
  if(curr == NULL) {

    return NULL;

  }

  /*single item queue*/
  if(q->size == 1) {

    q->head = NULL;
    q->size--;

    return curr;

  }

  while(curr->next) {

    curr = curr->next;

  }

  while(prev->next != curr) {

    prev = prev->next;

  }

  prev->next = NULL;
  q->size--;

  return curr;

}

/*main program*/

int scores[NUMTEAMS];
int penalty[NUMTEAMS][NUMPROBS];
int solved[NUMTEAMS][NUMPROBS];

void clear_data(void) {

  int i, j;

  for(i = 0; i < NUMTEAMS; i++) {

    scores[i] = -1;

  }

  for(i = 0; i < NUMTEAMS; i++) {

    for(j = 0; j < NUMPROBS; j++) {

      penalty[i][j] = 0;

    }

  }

  for(i = 0; i < NUMTEAMS; i++) {

    for(j = 0; j < NUMPROBS; j++) {

      solved[i][j] = 0;

    }

  }

}

int* array_from_input(void) {

  char line[BUFMAX] = {0};

  if(fgets(line,BUFMAX,stdin) == NULL) {

    return NULL;

  }

  if(line[0] == '\n') {

    return NULL;

  }

  if(strlen(line) < 6) {

    return NULL;

  }

  const char delim[2] = " ";

  char *token = strtok(line,delim);
  int *output = malloc(4*sizeof(int));
  int index = 0;
  
  while(token && index < 4) {

    if(index < 3) {

      output[index++] = (int)strtol(token,(char**)NULL,10);

    }else{

      output[index++] = (int)token[0];

    }

    token = strtok(NULL,delim);

  }

  return output;

}

/*redo*/
void update_scores(int *input) {

  int team = input[0];
  int problem = input[1];
  int time = input[2];
  char status = (char)input[3];

  /*account for teams that submit*/
  if(scores[team] < 0) {

    scores[team] = 0;

  }

  switch(status) {

  case 'C':

    if(solved[team][problem]) {

      break;

    }

    scores[team]++;
    penalty[team][problem] += time;
    solved[team][problem] = 1;
    break;

  case 'I':

    if(solved[team][problem]) {

      break;

    }

    penalty[team][problem] += 20;
    break;
    
  }

  return;

}

int read_input(void) {

  int *input = array_from_input();

  if(input == NULL) {

    return 0;

  }

  /*update scores*/
  update_scores(input);
  
  free(input);

  return 1;
  
}


void print_scores(void) {

  int i;
  Queue *q = create_queue();

  for(i = 0; i < NUMTEAMS; i++) {

    if(scores[i] >= 0) {

      /*calculate accrued valid penalty*/
      int valid_penalty = 0, j;

      for(j = 0; j < NUMPROBS; j++) {

	if(solved[i][j] == 1) {

	  valid_penalty += penalty[i][j];

	}

      }

      insert_in_order(q,i,scores[i],valid_penalty);
      
    }

  }

  while(!is_empty(q)) {

    Qnode *p = dequeue(q);

    printf("%d %d %d\n",p->team,p->score,p->penalty);

    free(p);

  }

}

int main(void) {

  /*read in num cases*/
  char input[BUFMAX];

  if(fgets(input,BUFMAX,stdin) == NULL) {

    return 1;

  }

  int num_cases = (int)strtol(input,(char**)NULL,10);
  int i;
  
  /*consume newline*/
  fgets(input,BUFMAX,stdin);
  
  /*for each case*/
  for(i = 0; i < num_cases; i++) {
    
    /*clear data*/
    clear_data();
    
    /*read input and calculate scores*/
    while(read_input());

    /*print scores*/
    print_scores();

    if(i < num_cases-1) {

      printf("\n");

    }

  }

}

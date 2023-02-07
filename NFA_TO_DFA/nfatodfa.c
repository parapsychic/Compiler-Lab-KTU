#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

typedef struct dfa_state{
  char states[MAX];
  int count;
} dfa_state;

typedef struct nfa_state{
  char states[MAX];
  int count;
} nfa_state;

char nfa_table[MAX][MAX][MAX];
int no_states;
int no_symbols;
int no_transitions;
char epsilon;

void parse_transition(int state, int symbol, char* transition){
  strcpy(nfa_table[state][symbol], transition);
}

void init_table(){
  for (int i = 0; i < no_states; i++) {
    for (int j = 0; j < no_symbols; j++) {
      strcpy(nfa_table[i][j], "-");
    }
  }
}

int main (int argc, char *argv[])
{
 printf("Enter the number of states: ");
 scanf("%d", &no_states);

 printf("Enter the number of symbols (last symbol is epsilon): ");
 scanf("%d", &no_symbols);
 epsilon = no_symbols + 97;
 printf("\n Epsilon = %c", epsilon);
 
 init_table();

 printf("Enter no of transitions: ");
 scanf("%d", &no_transitions);


 for (int i = 0; i < no_transitions; i++) {
  int state;
  char symbol, transition[MAX];
  scanf("%d %c %s", &state, &symbol, transition);
  parse_transition(state, symbol - 97, transition);
 }
 
  // print table:
  printf("NFA TABLE: \n");
  for (int i = 0; i < no_states; i++) {
    for (int j = 0; j < no_symbols; j++) {
      printf("%s\t",nfa_table[i][j] );
    }
    printf("\n");
  }

  e_closure(0);

  return 0;
}

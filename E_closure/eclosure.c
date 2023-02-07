#include<stdio.h>
#include<string.h>
#define SIZE 10

int no_States;
int eclosure[SIZE][SIZE];
int no_eclosure[SIZE];
int no_Transitions = 0;
FILE *file;
char input[SIZE][3];

void findClosure(int state){
  // add self to eclosure
  eclosure[state][no_eclosure[state]] = state;
  no_eclosure[state] ++;
  

    for (int j = 0; j < no_Transitions; j++) {
      if (input[j][0] == state + 48) {
        if (input[j][1] == 'e') {
          int next_state =  input[j][2] - 48;
          eclosure[state][no_eclosure[state]] = next_state;
          no_eclosure[state] ++;
          if (no_eclosure[next_state] == 0) {
            findClosure(next_state);
          }
          for (int k = 0; k < no_eclosure[next_state]; k++) {
             eclosure[state][no_eclosure[state]] = eclosure[next_state][k];
             no_eclosure[state] ++;
          }
        }
    }
  }

  printf("FOUNDING CLOSURE OF: %d\n", state);
  for (int i =0; i < no_States; i++) {
    printf("STATE %d :", i);
    for (int j = 0; j < no_eclosure[i]; j++) {
      printf("q%d ", eclosure[i][j]); 
    } 
    printf("\n");
  }
}

void init_arr(){
  for (int i = 0; i < no_States; i++) {
    no_eclosure[i] = 0;
    for (int j = 0; j < no_Transitions; j++) {
      eclosure[i][j] = '-';
    }
  }
  
}

void remove_duplicates(int *arr, int *size){
  for(int i=0; i<*size; i++){
          for(int j=i+1; j<*size; j++){
              if(arr[i] == arr[j]){
                  for(int k=j; k < *size - 1; k++){
                      arr[k] = arr[k + 1];
                  }
                  (*size)--;
                  j--;
              }
          }
      }
}


int main (int argc, char *argv[])
{
  printf("Enter the number of states: ");
  scanf("%d", &no_States);

  
  printf("The states are: ");
  for (int i = 0; i < no_States; i++) {
    printf("q%d ",i) ;
  }
  printf("\n");

  file = fopen("input", "r") ;
  if(!file){
    printf("Cannot find file!");
    return -1;
  }
  
  int line_no = 0;
  while (!feof(file)) {
    char start, alp, stop;
    fscanf(file, "%c %c %c\n", &start, &alp, &stop) ;
    printf("\n VERIFY: %c %c %c\n", start, alp, stop);
    input[line_no][0] = start;
    input[line_no][1] = alp;
    input[line_no][2] = stop;
    line_no++;
    no_Transitions++;
  }
  
  init_arr();
  for (int i = 0 ; i < no_Transitions; i++) {
    printf("%c %c %c\n", input[i][0], input[i][1], input[i][2] ) ;
  }

  for (int i = 0; i < no_States; i++) {
    if(no_eclosure[i] == 0)
      findClosure(i);
  }

  for (int i = 0; i < no_States; i++) {
    remove_duplicates(eclosure[i], &no_eclosure[i]);
  }

  for (int i = 0; i < no_States; i++) {
    printf("E-closure of q%d: { ", i);
    for (int j = 0; j < no_eclosure[i]; j++) {
      printf("q%d ", eclosure[i][j]); 
    } 
    printf("}\n");
  }


  
  return 0;
}

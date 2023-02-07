#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>
#define SIZE 10

// one-to-one mapping between all four arrays
// Productions of type S=Ab
// S      A     B   -> NT
// 1      2     1   -> no_Firsts 
// False True False -> has_epsilon
// a,b   a,Eps, b   -> firsts

// # is epsilon

char NT[SIZE];
int no_Firsts[SIZE];
bool has_epsilon[SIZE];
char firsts[SIZE][SIZE];

int no_Follows[SIZE];
char follows[SIZE][SIZE];

int no_NT = 0;
char prod[SIZE][SIZE];
int no_Prod;


int getIndex(char non_term){
  for (int i = 0; i < no_NT; i++) {
    if (NT[i] == non_term) {
      return i;
    }
  }
  return -1;
}

void first(char non_term, int index){
    for (int i = 0; i < no_Prod; i++) { // i loops over productions array
      if (prod[i][0] == non_term) { // is this production's LHS = the non_terminal we are calculating for
         for (int j = 2; prod[i][j] != 0 ; j++) { // j loops over RHS of ith production
           if (!isupper(prod[i][j])) { // this character is a terminal
              // # is epsilon
              if(prod[i][2] == '#') has_epsilon[index] = true;
              // copy terminal to firsts
             firsts[index][no_Firsts[index]] = prod[i][j];
             no_Firsts[index] ++;
              break;
           }
           else{
             // find first(Non terminal in RHS)
             int index_curr = getIndex(prod[i][j]); // index of current non terminal
             if (no_Firsts[index_curr] == 0) { // if we havent already calculated the first of that NT
              first(prod[i][j], index_curr);
             }

            // add all firsts from NT in RHS to the NT we are actually calculating
            for (int k = 0; k < no_Firsts[index_curr]; k++) {
              if(firsts[index_curr][k] == '#') {
                // if this is the last NT and it contains epsilon
                if (prod[i][j+1] == '\0') {
                  firsts[index][no_Firsts[index]] = '#';
                  no_Firsts[index]++;
                  has_epsilon[index] = true;
                }                
              }
              else{
                firsts[index][no_Firsts[index]] = firsts[index_curr][k];
                no_Firsts[index]++;
              }
            }
             
             // if the firsts have no epsilon, break 
             if (!has_epsilon[index_curr]) {
              break;
             } 
           }
          }  
        
      }
    }
}


void follow(char non_term, int index){
  if (non_term == 'S') { // if starting symbol, add $
    follows[index][no_Follows[index]] = '$';
    no_Follows[index] ++;
  } 

  
  for (int i = 0; i < no_Prod; i++) {
    for (int j = 2; prod[i][j] != 0; j++) {
      
      //if production contains the letter we want
      if (prod[i][j] == non_term) {
        
        // if last, do follow of [i][0]
       if (prod[i][j+1] == 0) {
       
         // last NT and LHS should not be same. eg. A=aA
         if (prod[i][j] != prod[i][0]) {
           int index_curr = getIndex(prod[i][0]);
           if (no_Follows[index_curr] == 0) {
             follow(prod[i][0], index_curr);
           }
           // add the follows to this NT's follows
           for (int l = 0; l < no_Follows[index_curr]; l++) {
             follows[index][no_Follows[index]] = follows[index_curr][l];
             no_Follows[index] ++;
           }
         }
       }
       
       else{
           // take the next letters one by one
           for (int k = j+1; true; k++) {
             // if out of alphabets on RHS, do follow of [i][0] like above (same code)
             if (prod[i][k] == 0) {
               // last NT and LHS should not be same. eg. A=aA
               if (prod[i][j] != prod[i][0]) {
                 int index_curr = getIndex(prod[i][0]);
                 if (no_Follows[index_curr] == 0) {
                   follow(prod[i][0], index_curr);
                 }
                 // add the follows to this NT's follows
                 for (int l = 0; l < no_Follows[index_curr]; l++) {
                   follows[index][no_Follows[index]] = follows[index_curr][l];
                   no_Follows[index] ++;
                 }
                 break;
               }
             }

             // if term, add it to follow. break
             if (!isupper(prod[i][k])) {
              follows[index][no_Follows[index]] = prod[i][k];
              no_Follows[index] ++;
              break;
             } 
             // if non term: find first. if !has epsilon,break
             if (isupper(prod[i][k])) {
               int index_curr = getIndex(prod[i][k]);
               for (int l = 0; l < no_Firsts[index_curr]; l++) {
                   printf("Before here %c \n", firsts[index_curr][l]);
                   if (firsts[index_curr][l] != '#') {
                        printf("In here\n");
                        follows[index][no_Follows[index]] = firsts[index_curr][l];
                        no_Follows[index]++;
                   }
               } 
               if (!has_epsilon[index_curr]) {
                 break;
               }
             } 

           }
        }
      } 
    }
  }
}

void remove_duplicates(char *arr, int *size){
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
  printf("Enter no of productions: ");
  scanf("%d", &no_Prod);

  printf("Enter the productions: ");
  
  for (int i = 0; i < no_Prod; i++) {
    scanf("%s", prod[i]);
    
    // is this a new non-terminal?
    int new_NT = true;
    for (int j = 0; j<i; j++) {
      if (prod[j][0] == prod[i][0]) {
          new_NT = false;
          break; 
      }
    }
    if(new_NT){
      NT[no_NT] = prod[i][0]; //if it is, add it to the NT array
      has_epsilon[no_NT] = false; //initializing the array
      
      no_Follows[no_NT] = 0;
      no_Firsts[no_NT] = 0;
      no_NT ++; 
    }

  }


  printf("Non terminals are: ");
  for (int i = 0; i < no_NT; i++) {
    printf("%c\t", NT[i]);
  }
  printf("\n");

  printf("Productions are: ");
  for (int i = 0; i < no_Prod; i++) {
    printf("%s\n", prod[i]);
  }
  
  
  printf("Calculating");

  printf("FIRST\n");
  for (int i = 0; i < no_NT; i++) {
    if (no_Firsts[i] == 0) { // did we calculate firsts for this NT earlier?
     first(NT[i], i); 
    }
  }

  for (int i = 0; i < no_NT; i++) {
    if (no_Follows[i] == 0) {
      follow(NT[i], i);
    }
  }
  

  printf("\n");
  for (int i = 0; i < no_NT; i++) {

    remove_duplicates(firsts[i], &no_Firsts[i]);
    printf("%c = ", NT[i]);
    for (int j = 0; j < no_Firsts[i]; j++) {
      printf("%c ", firsts[i][j]);
    }
    printf("\n");
  }


  printf("FOLLOW:\n");
  for (int i = 0; i < no_NT; i++) {
    remove_duplicates(follows[i], &no_Follows[i]);
    printf("%c = ", NT[i]);
    for (int j = 0; j < no_Follows[i]; j++) {
      printf("%c ", follows[i][j]);
    }
    printf("\n");
  }

  return 0;
}

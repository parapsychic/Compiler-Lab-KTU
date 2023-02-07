#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int no_Prod;
int no_NT = 0;
char NT[SIZE];
char prod[SIZE][SIZE];
char first[SIZE][SIZE];
int no_first[SIZE];
bool has_epsilon[SIZE];

char follow[SIZE][SIZE];
int no_follow[SIZE];


int getIndex(char s) {
  for (int i = 0; i < no_NT; i++) {
    if (NT[i] == s) {
      return i;
    }
  }
  return -1;
}

void find_first(char s, int index) {
  // i loops over prod arr
  for (int i = 0; i < no_Prod; i++) {
    // if lhs = required
    if (prod[i][0] == s) {
      //  j loops over prod j=2
      for (int j = 2; prod[i][j] != 0; j++) {
        //    if is terminal
        if (!isupper(prod[i][2])) {
          //      if is epsilon
          if (prod[i][j] == '#') {
            first[index][no_first[index]] = '#';
            no_first[index]++;
            has_epsilon[index] = true;
          }
          //      else copy
          else {
            first[index][no_first[index]] = prod[i][j];
            no_first[index]++;
          }
          break;
        } 
  //     else
        else {
          int index_curr = getIndex(prod[i][j]);
  //      check for firsts, calc first
          if (no_first[index_curr] == 0) {
            find_first(prod[i][j], index_curr);
          }
  //      copy it to first. copy epsilon only if j + 1 = 0
          for (int k = 0; k < no_first[index_curr]; k++) {
            if (first[index_curr][k] == '#') {
              if (prod[i][j + 1] == 0) {
                first[index][no_first[index]] = '#';
                no_first[index]++;
                has_epsilon[index] = true;
              }
            }
            else {
              first[index][no_first[index]] = first[index_curr][k];
              no_first[index]++;
            }
          }
  //      if j did not have epsilon, break
          if (!has_epsilon[index_curr]) {
            break;
          }
        }
      }
    }
  }
}

void find_follow(char s, int index){
  // if start, add $
  // i loops over prod arr
  //  j loops over prod
  //    if i,j is the letter we want
  //      if j+1 is 0 -> if LHS != i,j -> find follow LHS after checking and copy
  //      k loops from j+1 to end
  //        if k+1 is 0, repeat above code and break
  //        if i,k is terminal add it to follow
  //        else
  //          if 
  //         
}

int main(int argc, char *argv[]) {
  printf("Enter the productions: ");
  scanf("%d", &no_Prod);

  for (int i = 0; i < no_Prod; i++) {
    scanf("%s", prod[i]);
    // is this a new NT?
    bool newNT = true;
    for (int j = 0; j < i; j++) {
      if (prod[i][0] == prod[j][0]) {
        newNT = false;
      }
    }
    if (newNT) {
      NT[no_NT] = prod[i][0];
      has_epsilon[no_NT] = 0;
      no_first[no_NT] = 0;
      no_follow[no_NT] = 0;
      no_NT++;
    }
  }

  for (int i = 0; i < no_NT; i++) {
    if (no_first[i] == 0) {
      find_first(NT[i], i);
    }
  }

  for (int i = 0; i < no_NT; i++) {
    printf("First(%c): ", NT[i]);
    for (int j = 0; j < no_first[i]; j++) {
     printf("%c ", first[i][j]);
    }
    printf("\n");
  }

  return 0;
}

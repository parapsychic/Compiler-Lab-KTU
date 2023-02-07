#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

char stk[SIZE];
char buff[SIZE];

int buff_ptr = 0, stk_ptr = 0;
int len;

void check(){
  if (stk[stk_ptr] == 'i' && stk[stk_ptr + 1] == 'd') {
    stk[stk_ptr] = 'E';
    stk[stk_ptr + 1] = 0;

    printf("%s\t%s\tREDUCE\n", stk, buff);
  }
  
  for (int i = 0; i < len-2; i++) {
    if((stk[i] == 'E' && stk[i+1]=='+' && stk[i+2] == 'E') || 
       (stk[i] == 'E' && stk[i+1]=='*' && stk[i+2] == 'E') || 
       (stk[i] == '(' && stk[i+1]=='E' && stk[i+2] == ')')){
      stk[i] = 'E';
      stk[i+1] = 0; stk[i+2] = 0;
      printf("%s\t%s\tREDUCE\n", stk, buff);
      stk_ptr -= 1;
    }
  }
}


int main (int argc, char *argv[])
{
  printf("Grammar: \n");
  printf(" E->E+E \n E->E*E \n E->id \n E->(E)\n");

  
  printf("Enter the string to be parsed: ");
  scanf("%s", buff);
  len = strlen(buff);
  for (stk_ptr = 0; buff_ptr < len  ; stk_ptr++, buff_ptr++) {
    if(buff[buff_ptr] == 'i' && buff[buff_ptr + 1] == 'd') {
      stk[stk_ptr] = buff[buff_ptr];
      stk[stk_ptr + 1] = buff[buff_ptr + 1];
      stk[stk_ptr + 2] = 0;
      buff[buff_ptr] = ' ';
      buff[buff_ptr + 1] = ' ';
      buff_ptr++;      
      printf("\n%s\t%s\tSHIFT\n", stk, buff);
      check();
    }
    else{
      stk[stk_ptr] = buff[buff_ptr];
      buff[buff_ptr] = ' ';
      printf("\n%s\t%s\tSHIFT\n", stk, buff);
      check();
    }
  }
  check();

  if (stk[stk_ptr] == 'E') {
    printf("Parsing successful");
  } 
  else{
    printf("Parsing FAILED");
  }

  return 0;
}

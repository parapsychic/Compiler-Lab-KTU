#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10

bool E();
bool E_dash();
bool T();
bool T_dash();
bool F();

char *ip;
char buff[SIZE];

int main(){
  
  printf("Input the string: \n");
  scanf("%s", buff);
  ip = buff;

  if (E() && *ip == '\0') {
    printf("Parsing successful\n");
  }
  else printf("Parsing FAILED\n");

}

bool E(){
  if(T()){
    if(E_dash())
      return true;
  return false;
    
  }
}

bool E_dash(){
  if(*ip == '+'){
    ip++;
    if (T()) {
      if (E_dash()) {
       return true; 
      }
    }
    return false;
  }
  return true;
}

bool T(){
  if(F())
    if(T_dash())
      return true;
  return false;
}

bool T_dash(){
  if (*ip == '*') {
    ip++;
    if(F())
      if(T_dash())
        return true;
    return false;
  }
  return true;
}

bool F(){
  if(*ip == '('){
    ip++;
    if(E())
      if(*ip == ')'){
        ip++;
        return true;
      }
    return false;
  }
  else if (*ip == 'i') {
   ip++;
   if(*ip == 'd'){
     ip++;
     return true;
   }
  }
  return false;
}

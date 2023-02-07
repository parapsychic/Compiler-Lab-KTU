#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024

FILE *input;
char buffer[SIZE];

char delims[32] = {'{', '}', '(',  ')',  '[', ']', ' ', '+', '-', '*', '/',
                   '^', '%', '\t', '\n', ',', '.', ';', '<', '>', '='};
char keywords[17][10] = {"int",     "char", "float", "double",   "void",
                         "return",  "if",   "else",  "switch",   "for",
                         "while",   "do",   "break", "continue", "struct",
                         "typedef", "goto"};

bool isDelimiter(char c) {
  for (int i = 0; i < 21; i++) {
    if (c == delims[i]) {
      return true;
    }
  }
  return false;
}

bool isOperator(char c) {
  for (int i = 7; i < 11; i++) {
    if (c == delims[i]) {
      return true;
    }
  }
  return false;
}

bool isKeyword(char *string) {
  for (int i = 0; i < 17; i++) {
    if (strcmp(string, keywords[i]) == 0) {
      return true;
    }
  }
  return false;
}

bool isConstant(char *string) {
  if (string[0] == '"' && string[strlen(string) -1] == '"') {
    return true;
  }

  for (int i = 0; i < strlen(string); i++) {
    if (!isdigit(string[i]))
      return false;
  }
  return true;
}

bool isIdentifier(char *string) {
  if (isdigit(string[0])) {
    return false;
  }
  for (int i = 1; i < strlen(string); i++) {
    if (!isalnum(string[i]) && string[i] != '_') {
      return false;
    }
  }
  return true;
}

void parse(char *string) {
  // First check if this is a Delimiter
  // Then operator -> keyword -> constant -> identitfier
  int l = 0, r = 0;
  while (string[r] != 0 && l <= r) {
    
    //find constant strings:
    if (string[r] == '"') {
      // find match "
      int match = -1;
      for (int i = r + 1; i < strlen(string); i++) {
        if(string[i] == '"' ) {
          match = i;
          break;
        }
      }
     if (match == -1) {
      printf("Dangling \" error");
     } 
      
    r = match + 1;
    }

    else if (!isDelimiter(string[r])) {
      r++;
      continue;
    }
    // if pgm reaches here, we found a delimiter
    if (l == r) {
      // no string to the left of r.
      // l and r points to a delimiter
      if (isOperator(string[r])) {
        printf("%c is an operator \n", string[r]);
      }
      r++;
      l = r;
    }
    else {
      // extract string
      char substring[SIZE];
      strncpy(substring, string + l, r - l);
      substring[r-l] = 0;


     // detect stuff
     if(isKeyword(substring)){
       printf("%s is a keyword\n", substring);
     }
     else if(isConstant(substring)){
       printf("%s is a constant\n", substring);
     }
     else if(isIdentifier(substring)){
       printf("%s is a identifier\n", substring);
     }
     else{
       printf("%s could not be parsed\n", substring);
     }
     r++;
     l=r;
    }
  }
}

int main(int argc, char *argv[]) {
  char filename[16];
  printf("Enter the file to be parsed: ");
  scanf("%s", filename);

  input = fopen(filename, "r");

  if (!input) {
    printf("Cannot open file!\n");
    return -1;
  }

  bool isInComments = false;
  while (fgets(buffer, SIZE, input) != NULL) {
    int i = 0;
    // if a multiline comment start was detected, we need to find if this line
    // would end it eg, /* here isInComments=true this line would be ignore
    //      something */ isInComments would be false here and anything to the
    //      right of / would be parsed
    if (isInComments) {
      for (int j = 0; buffer[j + 1] != 0; j++) {
        if (buffer[j] == '*' && buffer[j + 1] == '/') {
          isInComments = false;
          i = j + 2; // sets the string to be parsed after the comments
          break;
        }
      }
      if (isInComments) { // if still in comments (if the end comment was not on
                          // this line), ignore this line
        continue;
      }
    }

    while (buffer[i] != 0 && (buffer[i] == ' ' || buffer[i] == '\t')) {
      i++;
    }

    // check if comment
    if (buffer[i] == '/' && buffer[i + 1] == '/') {
      continue;
    }

    if (buffer[i] == '/' && buffer[i + 1] == '*') {
      isInComments = true;
      continue;
    }

    if (buffer[i] == '#') {
      buffer[strlen(buffer) - 1] = 0;
      printf("%s is a preprocessor directive \n", buffer + i);
      continue;
    }
    // gives the string following the whitespace
    if (buffer[i] != 0) {
      parse(buffer + i);
    }
  }

  return 0;
}

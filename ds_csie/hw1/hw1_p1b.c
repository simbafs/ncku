#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define bool int
#define true 1
#define false 0

bool isOperator(char c) {
  switch (c) {
  case '+':
  case '-':
  case '*':
  case '/':
    return true;
  default:
    return false;
  }
}

int operatorPriority(char c) {
  switch (c) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  default:
    return 0;
  }
}

char *char2Str(char c) {
  char *str = (char *)malloc(2 * sizeof(char));
  str[0] = c;
  str[1] = '\0';
  return str;
}

int main() {
  char in[MAX_SIZE];
  scanf("%s", in);
  // infix to postfix

  // operator is placed in stack
  char *stack = (char *)malloc(MAX_SIZE * sizeof(char));
  int stackIdx = 0;

  for (int i = 0; i < strlen(in); i++) {
    if (isOperator(in[i])) {
      // if there are operators in the stack with higher or equal priority,
      // print them
      while (stackIdx > 0 &&
             operatorPriority(in[i]) <= operatorPriority(stack[stackIdx - 1])) {
        printf("%c", stack[--stackIdx]);
      }
      stack[stackIdx++] = in[i];
    } else {
      // operand is printed directly
      printf("%c", in[i]);
    }
  }

  while (stackIdx > 0) {
    printf("%c", stack[--stackIdx]);
  }
}

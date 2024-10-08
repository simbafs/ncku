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

char *char2Str(char c) {
  char *str = (char *)malloc(2 * sizeof(char));
  str[0] = c;
  str[1] = '\0';
  return str;
}

int main() {
  char in[MAX_SIZE];
  scanf("%s", in);

  char *stack[MAX_SIZE];
  int index = 0;

  for (int i = strlen(in) - 1; i >= 0; i--) {
    /* printf("i = %d, index = %d\n", i, index); */
    /* printf("queue: "); */
    /* for (int j = 0; j < index; j++) { */
    /*   printf("%s ", queue[j]); */
    /* } */
    /* printf("\n"); */
    if (isOperator(in[i])) {
      char *op = char2Str(in[i]);
      char *a = stack[index - 1];
      char *b = stack[index - 2];
      stack[index - 2] =
          (char *)malloc((strlen(a) + strlen(b) - 1) * sizeof(char));
      sprintf(stack[index - 2], "%s%s%s", a, op, b);
      index--;

    } else {
      stack[index++] = char2Str(in[i]);
    }
  }

  printf("%s\n", stack[0]);

  return 0;
}

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
  char data[MAX][MAX];
  int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }

int isEmpty(Stack *s) { return s->top == -1; }

void push(Stack *s, char *str) {
  if (s->top < MAX - 1) {
    s->top++;
    strcpy(s->data[s->top], str);
  } else {
    printf("Stack overflow\n");
  }
}

char *pop(Stack *s) {
  if (!isEmpty(s)) {
    return s->data[s->top--];
  }
  return NULL;
}

int isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

void prefixToInfix(char *prefix) {
  Stack s;
  initStack(&s);

  int length = strlen(prefix);

  for (int i = length - 1; i >= 0; i--) {
    char current = prefix[i];

    if (isOperator(current)) {
      char *op1 = pop(&s);
      char *op2 = pop(&s);

      char temp[MAX];
      sprintf(temp, "%s%c%s", op1, current, op2);

      push(&s, temp);
    }
    else if (isalnum(current)) {
      char operand[2] = {current, '\0'};
      push(&s, operand);
    }
  }

  printf("%s\n", pop(&s));
}

int main() {
  char prefix[MAX];

  scanf("%s", prefix);

  prefixToInfix(prefix);

  return 0;
}


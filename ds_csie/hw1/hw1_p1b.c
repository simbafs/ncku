#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
  char data[MAX_SIZE];
  int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }

int isEmpty(Stack *s) { return s->top == -1; }

int isFull(Stack *s) { return s->top == MAX_SIZE - 1; }

void push(Stack *s, char str) {
  if (!isFull(s)) {
    s->data[++s->top] = str;
  } else {
    printf("Stack overflow\n");
  }
}

char pop(Stack *s) {
  if (!isEmpty(s)) {
    return s->data[s->top--];
  } else {
    return 0;
  }
}

int isOperator(char c) {
  switch (c) {
  case '+':
  case '-':
  case '*':
  case '/':
    return 1;
  default:
    return 0;
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

int infixToPostfix(char *in) {
  Stack s;
  initStack(&s);

  char out[MAX_SIZE];

  int outIdx = 0;
  for (int i = 0; i < strlen(in); i++) {
    if (isOperator(in[i])) {
      while (!isEmpty(&s) &&
             operatorPriority(in[i]) <= operatorPriority(s.data[s.top])) {
        out[outIdx++] = s.data[s.top--];
      }
      s.data[++s.top] = in[i];
    } else {
      out[outIdx++] = in[i];
    }
  }

  while (!isEmpty(&s)) {
    out[outIdx++] = s.data[s.top--];
  }

  out[outIdx] = '\0';
  printf("%s\n", out);
}

int main() {
  char in[MAX_SIZE];
  scanf("%s", in);

  infixToPostfix(in);
  return 0;
}

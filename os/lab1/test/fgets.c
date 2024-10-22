#include <stdio.h>

int main(){
  FILE *file = fopen("input.txt", "r");
  char buf[1024];

  // read the file line by line

  while (fgets(buf, 1024, file) != NULL) {
    printf("%s", buf);
  }

  return 0;
}

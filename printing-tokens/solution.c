#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *input = malloc(sizeof(char) * 1000);
  for (int i = 0; i < 1000; ++i) {
    *(input + i) = -1;
  }
  scanf("%[^\n]", input);
  int i = 0, j = 0;
  while (*(input + i) != -1) {
    if ((*(input + i)) == ' ') {
      *(input + i) = (char)'\0';
      printf("%s\n", input + j);
      j = i + 1;
    }
    ++i;
  }
  printf("%s\n", input + j);
  return 0;
}

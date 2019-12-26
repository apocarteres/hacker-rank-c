#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int *result = calloc(10, sizeof(int));
  char *input = malloc(sizeof(char) * 1000);
  for (int i = 0; i < 1000; ++i) {
    *(input + i) = -1;
  }
  scanf("%s", input);
  int i = 0;
  while (*(input + i) != -1) {
    if (isdigit(*(input + i))) {
      int d = *(input + i);
      d -= '0';
      if (d >= 0 && d <= 9) {
        *(result + d) = *(result + d) + 1;
      }
    }
    ++i;
  }
  for (int i = 0; i < 10; ++i) {
    printf("%d ", *(result + i));
  }
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  return 0;
}

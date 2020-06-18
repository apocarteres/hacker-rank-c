#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcDiff(const char *str) {
  char table[1024];
  for (int i = 0; i < 1024; ++i) {
    table[i] = 0;
  }
  int i = 0;
  while (*(str + i) != '\0') {
    table[*(str + i)] = 1;
    ++i;
  }
  int diff = 0;
  for (i = 0; i < 1024; ++i) {
    if (table[i] == 1) {
      ++diff;
    }
  }
  return diff;
}

void swap(char **arr, int i, int j) {
  char *tmp = *(arr + i);
  *(arr + i) = *(arr + j);
  *(arr + j) = tmp;
}

int lexicographic_sort(const char *a, const char *b) { return strcmp(a, b); }

int lexicographic_sort_reverse(const char *a, const char *b) {
  return lexicographic_sort(b, a);
}

int sort_by_number_of_distinct_characters(const char *a, const char *b) {
  int diff_a = calcDiff(a);
  int diff_b = calcDiff(b);
  int diff = diff_a - diff_b;
  if (!diff) {
    return lexicographic_sort(a, b);
  }
  return diff;
}

int sort_by_length(const char *a, const char *b) {
  int diff = strlen(a) - strlen(b);
  if (!diff) {
    return lexicographic_sort(a, b);
  }
  return diff;
}

void string_sort(char **arr, const int len,
                 int (*cmp_func)(const char *a, const char *b)) {
  for (int i = 0; i < len; ++i) {
    char *str_a = (char *)*(arr + i);
    for (int j = i; j < len; ++j) {
      char *str_b = (char *)*(arr + j);
      if (cmp_func(str_a, str_b) > 0) {
        swap(arr, i, j);
        string_sort(arr, len, cmp_func);
        break;
      }
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);

  char **arr;
  arr = (char **)malloc(n * sizeof(char *));

  for (int i = 0; i < n; i++) {
    *(arr + i) = malloc(1024 * sizeof(char));
    scanf("%s", *(arr + i));
    *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
  }

  string_sort(arr, n, lexicographic_sort);
  for (int i = 0; i < n; i++)
    printf("%s\n", arr[i]);
  printf("\n");

  string_sort(arr, n, lexicographic_sort_reverse);
  for (int i = 0; i < n; i++)
    printf("%s\n", arr[i]);
  printf("\n");

  string_sort(arr, n, sort_by_length);
  for (int i = 0; i < n; i++)
    printf("%s\n", arr[i]);
  printf("\n");

  string_sort(arr, n, sort_by_number_of_distinct_characters);
  for (int i = 0; i < n; i++)
    printf("%s\n", arr[i]);
  printf("\n");
}

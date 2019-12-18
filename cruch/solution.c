#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();
char **split_string(char *);

#define APCRT_DEBUG(...) printf(__VA_ARGS__)

#ifndef APCRT_DEBUG
#define APCRT_DEBUG(...)                                                       \
  do {                                                                         \
  } while (0)
#endif

typedef long long int64;

typedef struct _array {
  int rows;
  int cols;
  int64 **data;
} array;

void allocate_array(int rows, int cols, array *arr) {
  int64 **data = malloc(sizeof(int64 *) * cols);
  for (int i = 0; i < cols; ++i) {
    *(data + i) = calloc(rows, sizeof(int64));
    APCRT_DEBUG("allocated rows at column %d with addr %p\n", i, *(data + i));
  }
  arr->rows = rows;
  arr->cols = cols;
  arr->data = data;
}

void debug_array(array *arr) {
  APCRT_DEBUG("\n ---- array output --- \n");
  for (int r = 0; r < arr->rows; ++r) {
    for (int c = 0; c < arr->cols; ++c) {
      int64 *col = *(arr->data + c);
      int64 *row = (col + r);
      APCRT_DEBUG(" %ld ", *row);
    }
    APCRT_DEBUG("\n");
  }
}

int64 add_value(array *arr, int from, int to, int64 value) {
  --from;
  --to;
  int64 max_value = value;
  for (int c = from; c <= to; ++c) {
    int64 *col = *(arr->data + c);
    for (int r = 0; r < arr->rows; ++r) {
      int64 *row = (col + r);
      *row += value;
      if (*row > max_value) {
        max_value = *row;
      }
    }
  }
  return max_value;
}

int calc_max_index(int queries_rows, int **queries) {
  int max_index = 0;
  for (int i = 0; i < queries_rows; ++i) {
    int *c = *(queries + i);
    int a = *c;
    int b = *(c + 1);
    int64 k = *(c + 2);
    max_index = b > max_index ? b : max_index;
  }
  APCRT_DEBUG("max index found is %d\n", max_index);
  return max_index;
}

int64 run_queries(array *arr, int queries_rows, int **queries) {
  int64 result = 0;
  for (int i = 0; i < queries_rows; ++i) {
    int *c = *(queries + i);
    int a = *c;
    int b = *(c + 1);
    int64 k = *(c + 2);
    int64 max = add_value(arr, a, b, k);
    if (max > result) {
      result = max;
    }
    debug_array(arr);
    APCRT_DEBUG("new result is %ld\n", result);
  }
  return result;
}

// Complete the arrayManipulation function below.
long arrayManipulation(int n, int queries_rows, int queries_columns,
                       int **queries) {
  array arr = {0, 0, NULL};
  allocate_array(n, calc_max_index(queries_rows, queries), &arr);
  return run_queries(&arr, queries_rows, queries);
}

int main() {
  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  char **nm = split_string(readline());

  char *n_endptr;
  char *n_str = nm[0];
  int n = strtol(n_str, &n_endptr, 10);

  if (n_endptr == n_str || *n_endptr != '\0') {
    exit(EXIT_FAILURE);
  }

  char *m_endptr;
  char *m_str = nm[1];
  int m = strtol(m_str, &m_endptr, 10);

  if (m_endptr == m_str || *m_endptr != '\0') {
    exit(EXIT_FAILURE);
  }

  int **queries = malloc(m * sizeof(int *));

  for (int i = 0; i < m; i++) {
    *(queries + i) = malloc(3 * (sizeof(int)));

    char **queries_item_temp = split_string(readline());

    for (int j = 0; j < 3; j++) {
      char *queries_item_endptr;
      char *queries_item_str = *(queries_item_temp + j);
      int queries_item = strtol(queries_item_str, &queries_item_endptr, 10);

      if (queries_item_endptr == queries_item_str ||
          *queries_item_endptr != '\0') {
        exit(EXIT_FAILURE);
      }

      *(*(queries + i) + j) = queries_item;
    }
  }

  int queries_rows = m;
  int queries_columns = 3;

  long result = arrayManipulation(n, queries_rows, queries_columns, queries);

  fprintf(fptr, "%ld\n", result);

  fclose(fptr);

  return 0;
}

char *readline() {
  size_t alloc_length = 1024;
  size_t data_length = 0;
  char *data = malloc(alloc_length);

  while (true) {
    char *cursor = data + data_length;
    char *line = fgets(cursor, alloc_length - data_length, stdin);

    if (!line) {
      break;
    }

    data_length += strlen(cursor);

    if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
      break;
    }

    size_t new_length = alloc_length << 1;
    data = realloc(data, new_length);

    if (!data) {
      break;
    }

    alloc_length = new_length;
  }

  if (data[data_length - 1] == '\n') {
    data[data_length - 1] = '\0';
  }

  data = realloc(data, data_length);

  return data;
}

char **split_string(char *str) {
  char **splits = NULL;
  char *token = strtok(str, " ");

  int spaces = 0;

  while (token) {
    splits = realloc(splits, sizeof(char *) * ++spaces);
    if (!splits) {
      return splits;
    }

    splits[spaces - 1] = token;

    token = strtok(NULL, " ");
  }

  return splits;
}

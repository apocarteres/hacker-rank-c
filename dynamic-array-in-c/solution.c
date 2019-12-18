#include <stdio.h>
#include <stdlib.h>

/*
 * This stores the total number of books in each shelf.
 */
int *total_number_of_books;

/*
 * This stores the total number of pages in each book of each shelf.
 * The rows represent the shelves and the columns represent the books.
 */
int **total_number_of_pages;

//#define APCRT_DEBUG(...) printf(__VA_ARGS__)

#ifndef APCRT_DEBUG
#define APCRT_DEBUG(...)                                                       \
  do {                                                                         \
  } while (0)
#endif

void allocate_shelves(int new_shelve_count) {
  total_number_of_books = malloc(sizeof(int) * new_shelve_count);
  for (int i = 0; i < new_shelve_count; ++i) {
    *(total_number_of_books + i) = 0;
  }
  total_number_of_pages = malloc(sizeof(int *) * new_shelve_count);
  for (int i = 0; i < new_shelve_count; ++i) {
    *(total_number_of_pages + i) = malloc(sizeof(int));
  }
}

void resize_books(int **books_ptr, int new_books_count) {
  int *old_books = *books_ptr;
  int *new_books = malloc(sizeof(int) * new_books_count);
  for (int i = 0; i < new_books_count - 1; ++i) {
    *(new_books + i) = *(*books_ptr + i);
  }
  *books_ptr = new_books;
  free(old_books);
}

void insertBook(int shelve_index, int pages) {
  int *books_count = (total_number_of_books + shelve_index);
  APCRT_DEBUG("current amount of books at shelve %d is %d\n", shelve_index,
              *books_count);
  APCRT_DEBUG("adding book with %d pages to the end of %d\n", pages,
              shelve_index);
  int *books = *(total_number_of_pages + shelve_index);
  APCRT_DEBUG("book ptr before resize: %p\n", (void *)books);
  if (*books_count % 100 == 0) {
    int new_books_count = *books_count + 100;
    APCRT_DEBUG("resizing books from %d to %d at shelve %d\n", *books_count,
                new_books_count, shelve_index);
    resize_books(&books, new_books_count);
  }
  APCRT_DEBUG("book ptr after resize: %p\n", (void *)books);
  *(books + *books_count) = pages;
  *(total_number_of_pages + shelve_index) = books;
  *books_count = *books_count + 1;
  APCRT_DEBUG("there are %d books at shelve %d: [", *books_count, shelve_index);
  for (int i = 0; i < *books_count; ++i) {
    APCRT_DEBUG(" %d ", *(books + i));
  }
  APCRT_DEBUG("]\n");
}

int main() {
  int total_number_of_shelves;
  scanf("%d", &total_number_of_shelves);
  allocate_shelves(total_number_of_shelves);

  int total_number_of_queries;
  scanf("%d", &total_number_of_queries);

  while (total_number_of_queries--) {
    int type_of_query;
    scanf("%d", &type_of_query);

    if (type_of_query == 1) {
      /*
       * Process the query of first type here.
       */
      int x, y;
      scanf("%d %d", &x, &y);
      insertBook(x, y);
    } else if (type_of_query == 2) {
      int x, y;
      scanf("%d %d", &x, &y);
      printf("%d\n", *(*(total_number_of_pages + x) + y));
    } else {
      int x;
      scanf("%d", &x);
      printf("%d\n", *(total_number_of_books + x));
    }
  }

  if (total_number_of_books) {
    free(total_number_of_books);
  }

  for (int i = 0; i < total_number_of_shelves; i++) {
    if (*(total_number_of_pages + i)) {
      free(*(total_number_of_pages + i));
    }
  }

  if (total_number_of_pages) {
    free(total_number_of_pages);
  }

  return 0;
}

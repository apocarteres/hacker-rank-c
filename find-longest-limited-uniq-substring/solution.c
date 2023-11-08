#include <stdio.h>
#include <string.h>

#define MAX_ASCII_LENGTH 256

static char table_of_uniq[MAX_ASCII_LENGTH];

void reset_table() {
    memset(table_of_uniq, 0, sizeof(char) * MAX_ASCII_LENGTH);
}

//approximately O(n) time and O(C) storage;
size_t count_uniq_lengths(const char *str, size_t len, size_t limit_uniq) {
    size_t uniq = 0;
    size_t last_mark = 0;
    size_t max_length = 0;
    reset_table();
    for (size_t i = 0; i < len; ++i) {
        char c = *(str + i);
        if (!(table_of_uniq[c])) {
            table_of_uniq[c] = 1;
            ++uniq;
            if (uniq > limit_uniq) {
                uniq = 1;
                reset_table();
                table_of_uniq[c] = 1;
                size_t v = i - last_mark;
                if (v > max_length) {
                    max_length = v;
                }
                last_mark = i - 1;
            }
        }
    }
    size_t v = len - last_mark;
    if (v > max_length) {
        return v;
    }
    return max_length;
}

void run_test(const char* str, size_t max_uniq, size_t expected) {
    printf("%s: ", str);
    size_t result = count_uniq_lengths(str, strlen(str), max_uniq);
    if (result == expected) {
        printf("OK, max uniq: %ld, result: %ld", max_uniq, result);
    } else {
        printf("FAILED. Expected %ld, but got %ld for", expected, result);
    }
    printf("\n");
}

int main() {
    run_test("eceba", 2, 3);
    run_test("abcabababababaddddd", 2, 11);
    run_test("abc", 2, 2);
    run_test("aaabdddd", 2, 5);
    run_test("a", 2, 1);
    run_test("aaaa", 2, 4);
    run_test("aaaab", 2, 5);
    run_test("abacbdabab", 3, 6);
    run_test("abcdeedcba", 5, 10);
    return 0;
}


#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERN 2000
#define MAX_LINE_LENGTH 5000

typedef struct {
  int e, i, v, c, l, n, h, s, f, o;
} Flags;

Flags flag = {0};

int parser(int argc, char *argv[], regex_t *pattern, int *count_pattern);
int print_matches(regex_t *pattern, int count_pattern, char *filename);
int read_file_pattern(regex_t *pattern, int *count_pattern, char *filename);
void free_pattern(regex_t *pattern, int count);

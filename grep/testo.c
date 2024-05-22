#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int count_pattern = 0;
  regex_t pattern[MAX_PATTERN];
  int error = parser(argc, argv, pattern, &count_pattern);

  if (!error) {
    while (optind < argc) {
      if (print_matches(pattern, count_pattern, argv[optind]) && !flag.s)
        printf("%s: No such file or directory\n", argv[optind]);
      optind++;
    }
  } else {
    printf("Error!\n");
  }

  free_pattern(pattern, count_pattern);

  return 0;
}

int parser(int argc, char *argv[], regex_t *pattern, int *count_pattern) {
  char get_opt;
  int error = 0;

  while (!error && (get_opt = getopt(argc, argv, ":e:ivclnhsf:o")) != -1) {
    switch (get_opt) {
      case 'f':
        flag.f = 1;
        if ((error = read_file_pattern(pattern, count_pattern, optarg)))
          printf("%s: No such file or directory\n", optarg);
        break;
      case 'e':
        flag.e = 1;
        regcomp(&pattern[*count_pattern], optarg,
                flag.i ? REG_ICASE : REG_EXTENDED);
        (*count_pattern)++;
        break;
      case 'i':
        flag.i = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 'c':
        flag.c = 1;
        break;
      case 'l':
        flag.l = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'h':
        flag.h = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'o':
        flag.o = 1;
        break;
      default:
        error = 1;
        break;
    }
  }

  if (!error && (optind + 1 - (flag.f || flag.e)) < argc) {
    if (!(flag.f || flag.e)) {
      regcomp(&pattern[*count_pattern], argv[optind],
              flag.i ? REG_ICASE : REG_EXTENDED);
      (*count_pattern)++;
      optind++;
    }
    if (optind == argc - 1) flag.h = 1;
  } else {
    error = 1;
  }

  return error;
}

int print_matches(regex_t *pattern, int count_pattern, char *filename) {
  int result, line_len, line_count = 0, match_count = 0, offset = 0;
  char line[MAX_LINE_LENGTH], match = 0;
  FILE *f = fopen(filename, "r");

  !f ? (result = 0) : (result = 1);

  while (result && feof(f) == 0 && fgets(line, MAX_LINE_LENGTH, f)) {
    match = 0;
    line_len = strlen(line);
    line_count++;
    for (int i = 0; i < count_pattern; i++) {
      offset = 0;
      regmatch_t regmatch;
      while (!regexec(&pattern[i], &line[offset], 1, &regmatch, 0)) {
        if (flag.o && !flag.v && !flag.c && !flag.l) {
          if (!offset && !flag.h) printf("%s:", filename);
          if (!offset && flag.n) printf("%d:", line_count);
          while (regmatch.rm_so < regmatch.rm_eo) {
            printf("%c", line[offset + regmatch.rm_so]);
            regmatch.rm_so++;
          }
          printf("\n");
        }
        match = 1;
        offset += regmatch.rm_eo;
      }
    }
    if (flag.v) match = !match;

    match_count += match;

    if (match && !flag.c && !flag.l && (!flag.o || flag.v)) {
      if (!flag.h) printf("%s:", filename);
      if (flag.n) printf("%d:", line_count);
      for (int i = 0; i < line_len && line[i] != '\n'; i++)
        printf("%c", line[i]);
      printf("\n");
    }
  }

  if (flag.c) {
    if (!flag.h) printf("%s:", filename);
    if (flag.l) match_count = 1;
    printf("%d\n", match_count);
  }

  if (flag.l)
    if (match_count > 0) printf("%s\n", filename);

  if (result) fclose(f);

  return !result;
}

void free_pattern(regex_t *pattern, int count) {
  for (int i = 0; i < count; i++) regfree(&pattern[i]);
}

int read_file_pattern(regex_t *pattern, int *count_pattern, char *filename) {
  int result, line_len;
  char line[MAX_LINE_LENGTH];
  FILE *f = fopen(filename, "r");

  !f ? (result = 0) : (result = 1);

  while (result && feof(f) == 0 && fgets(line, MAX_LINE_LENGTH, f)) {
    line_len = strlen(line);

    if (line[line_len - 1] == '\n') line[line_len - 1] = '\0';

    regcomp(&pattern[(*count_pattern)++], line,
            flag.i ? REG_ICASE : REG_EXTENDED);
  }

  if (result) fclose(f);

  return !result;
}

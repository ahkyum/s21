#include "s21_cat.h"

int main(int argc, char* argv[]) {
  if (argc == 2) {
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) return 1;
    int c;
    while ((c = fgetc(fp)) != EOF) {
      putchar(c);
    }
  }

  if (argc < 2) {
    printf("Недостаточно аргументов командной строки.\n");
    return 1;
  }

  FILE* fp = fopen(argv[2], "r");
  if (fp == NULL) return 1;

  char arg[MAX_ARG_LEN];
  strncpy(arg, argv[1], MAX_ARG_LEN - 1);
  arg[MAX_ARG_LEN - 1] = '\0';

  if ((arg[1] == 'e') || (arg[1] == 'E'))
    flag_e_dollar(fp);
  else if ((arg[1] == 't') || (arg[1] == 'T'))
    flag_t_tabs(fp);
  else if ((arg[1] == 'b') || (arg[9] == 'n'))
    flag_b_nepust(fp);
  else if ((arg[1] == 'n') || (arg[2] == 'n'))
    flag_n_vse(fp);
  else if ((arg[1] == 's') || (arg[2] == 's'))
    flag_s_squeeze(fp);

  fclose(fp);
  return 0;
}

void flag_e_dollar(FILE* fp) {
  char replace_chars[2] = "$";
  int c;
  while ((c = fgetc(fp)) != EOF) {
    if (c == '\n') {
      printf("%s\n", replace_chars);
    } else {
      putchar(c);
    }
  }
}

void flag_t_tabs(FILE* fp) {
  char replace_chars[3] = "^I";
  int c;
  while ((c = fgetc(fp)) != EOF) {
    if (c == '\t') {
      printf("%s", replace_chars);
    } else {
      putchar(c);
    }
  }
}

void flag_b_nepust(FILE* fp) {
  char line[500];
  int line_number = 1;
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (strcmp(line, "\n") == 0) {
      printf("%s", line);
    } else {
      printf("%6d\t%s", line_number, line);
      line_number++;
    }
  }
}

void flag_n_vse(FILE* fp) {
  char line[500];
  int line_number = 1;
  while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%6d\t%s", line_number, line);
    line_number++;
  }
}

void flag_s_squeeze(FILE* fp) {
  char line[500];
  char prev_line[500] = "";
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (strcmp(line, "\n") == 0) {
      if (strcmp(prev_line, "\n") != 0) {
        printf("%s", line);
      }
    } else {
      printf("%s", line);
    }
    strcpy(prev_line, line);
  }
}

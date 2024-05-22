#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

#define MAX_ARG_LEN 100

void flag_e_dollar(FILE* fp);
void flag_t_tabs(FILE* fp);
void flag_b_nepust(FILE* fp);
void flag_n_vse(FILE* fp);
void flag_s_squeeze(FILE* fp);

#endif

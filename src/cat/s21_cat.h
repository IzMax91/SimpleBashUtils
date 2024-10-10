#ifndef S21_CAT_H
#define S21_CAT_H
#include <stdio.h>
#include <string.h>

struct flags {
  char name_flag;
  char long_name_flag[20];
  int status_flag;
};

int flag_definition(char flag, struct flags* all_flags);
int long_flag_definition(char* long_flag, struct flags* all_flags);
void print_file(char* name, struct flags* all_flags);

void flag_e();
void flag_s(FILE* fp, char* ch);
void flag_n(int* counter, int* printed_n);
void flag_b(int* counter);
void flag_t(FILE* fp, char* ch);
void flag_v(char* ch);
void print_num(int* counter);

#endif
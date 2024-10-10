#ifndef S21_GREP_H
#define S21_GREP_H
#include <stdio.h>
#include <string.h>

struct flags {
  char name;
  int status;
};

struct template_or_file {
  int status;
  int position_ef;
};

void flag_definition(char flag8, struct flags* all_flags);
void open_file(int argc, char* argv[], struct flags* all_flags,
               struct template_or_file* t_or_f);

void file_line(FILE* fp, char* text, char* ch);
void matching_search(int argc, char* argv[], struct template_or_file* t_or_f,
                     char* text, char* name_file, struct flags* all_flags,
                     int* counter, int line_number, int* bool_flag_l);
void print_grep(int* counter, struct template_or_file* t_or_f,
                struct flags* all_flags, char* name_file, int line_number,
                char* text, int* bool_flag_l, char* search, int num);
void search_array(char* argv, int pos_e, char* search);
int comparison(int flag_i, int flag_o, char* text, char* search, int* num);
void case_change(char* array, char* text, int flag);

#endif
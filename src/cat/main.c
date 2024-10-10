#include "s21_cat.h"

int main(int argc, char* argv[]) {
  int not_name = 1;
  int error_flag = 0;
  char flag_not_found = ' ';
  struct flags all_flags[6] = {
      {'b', "--number-nonblank", 0}, {'e', "-E", 0}, {'n', "--number", 0},
      {'s', "--squeeze-blank", 0},   {'t', "-T", 0}, {'v', "-V", 0}};

  for (int i = 1; i < argc && !error_flag; i++) {
    if (argv[i][0] == '-' && not_name) {
      if (long_flag_definition(argv[i], all_flags)) {
        for (size_t j = 1; j < strlen(argv[i]) && !error_flag; j++)
          if (flag_definition(argv[i][j], all_flags)) {
            error_flag = 1;
            flag_not_found = argv[i][j];
          }
      }
    } else {
      not_name = 0;
      print_file(argv[i], all_flags);
    }
  }

  if (error_flag) {
    printf("s21_cat: illegal option -- %c", flag_not_found);
    printf("\nusage: cat [-benstuv] [file ...]");
  }
  return 0;
}
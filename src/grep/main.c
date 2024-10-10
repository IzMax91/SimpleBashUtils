#include "s21_grep.h"

#define MAX_ARGC 100

int main(int argc, char *argv[]) {
  struct flags all_flags[10] = {{'e', 0}, {'i', 0}, {'v', 0}, {'c', 0},
                                {'l', 0}, {'n', 0}, {'h', 0}, {'s', 0},
                                {'f', 0}, {'o', 0}};
  struct template_or_file t_or_f[MAX_ARGC] = {};
  t_or_f[0].status = 0;

  int template_true = 0;
  int possible_file = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-')
      for (size_t j = 1; j < strlen(argv[i]); j++) {
        flag_definition(argv[i][j], all_flags);

        if (argv[i][j] == 'e' || argv[i][j] == 'f') {
          int n;
          if (argv[i][j] == 'f')
            n = 3;
          else
            n = 0;

          template_true = 1;
          if (possible_file > 0) {
            t_or_f[possible_file].status = 3;
            t_or_f[0].status = 1;
          }
          if (j + 1 == strlen(argv[i])) {
            t_or_f[i + 1].status = 1 + n;
            i++;
          } else {
            t_or_f[i].status = 2 + n;
            t_or_f[i].position_ef = j;
          }
          j = strlen(argv[i]);
        }
      }

    else if (!template_true) {
      t_or_f[i].status = 1;
      template_true = 1;
      possible_file = i;
    } else {
      if (t_or_f[0].status < 2) t_or_f[0].status++;
      t_or_f[i].status = 3;
    }
  }

  open_file(argc, argv, all_flags, t_or_f);

  return 0;
}

#include "s21_cat.h"

int flag_definition(char flag, struct flags* all_flags) {
  for (int i = 0; i < 6; i++) {
    if (flag == all_flags[i].name_flag) {
      all_flags[i].status_flag = 1;
      return 0;
    }
  }
  return 1;
}

int long_flag_definition(char* long_flag, struct flags* all_flags) {
  for (int i = 0; i < 5; i++) {
    if (strcmp(long_flag, all_flags[i].long_name_flag) == 0) {
      all_flags[i].status_flag = 1;
      if (strlen(long_flag) == 2) all_flags[i].status_flag++;

      return 0;
    }
  }
  return 1;
}

void print_file(char* name, struct flags* all_flags) {
  FILE* fp = fopen(name, "r");
  if (fp) {
    int counter = 1;
    int printed_n = 0;

    char old_ch = '\n';
    char new_ch = getc(fp);

    while (new_ch != EOF) {
      if (all_flags[3].status_flag && new_ch == '\n' && old_ch == '\n')
        flag_s(fp, &new_ch);

      if (all_flags[2].status_flag && !all_flags[0].status_flag &&
          (old_ch == '\n' || printed_n))
        flag_n(&counter, &printed_n);

      if (all_flags[0].status_flag && new_ch != '\n' && new_ch != EOF &&
          old_ch == '\n')
        flag_b(&counter);

      if (all_flags[4].status_flag && new_ch == '\t') flag_t(fp, &new_ch);
      if (all_flags[1].status_flag && (new_ch == '\n' || new_ch == EOF))
        flag_e();
      if (all_flags[5].status_flag || all_flags[4].status_flag == 1 ||
          all_flags[1].status_flag == 1)
        flag_v(&new_ch);
      if (new_ch != EOF) {
        printf("%c", new_ch);

        old_ch = new_ch;
        new_ch = getc(fp);
      } else
        printf("\n");
    }

  } else
    printf("s21_cat: %s: No such file or directory", name);
  fclose(fp);
}

void flag_n(int* counter, int* printed_n) {
  print_num(counter);
  *counter += 1;
  *printed_n = 0;
}

void flag_b(int* counter) {
  print_num(counter);
  *counter += 1;
}

void flag_e() { printf("%c", '$'); }
void flag_t(FILE* fp, char* ch) {
  while (*ch == '\t') {
    printf("%s", "^I");
    *ch = getc(fp);
  }
}

void flag_v(char* ch) {
  if ((*ch >= 0 && *ch <= 31 && *ch != 9 && *ch != 10) || *ch == 127) {
    if (*ch == 127) {
      printf("^");
      *ch = '?';
    } else {
      printf("^");
      *ch = *ch + 64;
    }
  }
}

void flag_s(FILE* fp, char* ch) {
  while (*ch == '\n') {
    *ch = getc(fp);
  }
  if (*ch != EOF) {
    fseek(fp, ftell(fp) - 2, SEEK_SET);
    *ch = getc(fp);
  }
}

void print_num(int* counter) {
  int x = 100000;
  while (*counter / x == 0) {
    printf(" ");
    x /= 10;
  }
  printf("%d\t", *counter);
}

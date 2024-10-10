#include "s21_grep.h"

void flag_definition(char flag, struct flags *all_flags) {
  for (int i = 0; i < 10; i++)
    if (flag == all_flags[i].name) {
      all_flags[i].status = 1;
      i = 10;
    }
}

void open_file(int argc, char *argv[], struct flags *all_flags,
               struct template_or_file *t_or_f) {
  for (int i = 1; i < argc; i++)
    if (t_or_f[i].status == 3) {
      FILE *fp = fopen(argv[i], "r");
      if (fp) {
        char ch = getc(fp);
        int counter = 0;
        int bool_flag_l = 0;
        for (int j = 1; ch != EOF && !bool_flag_l; j++) {
          char text[10024] = {'\0'};
          file_line(fp, text, &ch);
          matching_search(argc, argv, t_or_f, text, argv[i], all_flags,
                          &counter, j, &bool_flag_l);
          ch = getc(fp);
        }
        if (all_flags[3].status) {
          if (t_or_f[0].status >= 2 && !all_flags[6].status)
            printf("%s:", argv[i]);
          printf("%d\n", counter);
        }
        if (all_flags[4].status && counter > 0) printf("%s\n", argv[i]);
      } else if (!all_flags[7].status)
        printf("grep: %s: No such file or directory\n", argv[i]);
      fclose(fp);
    }
}

void file_line(FILE *fp, char *text, char *ch) {
  for (int i = 0; *ch != '\n' && *ch != EOF; i++) {
    text[i] = *ch;
    *ch = getc(fp);
  }
}

void matching_search(int argc, char *argv[], struct template_or_file *t_or_f,
                     char *text, char *name_file, struct flags *all_flags,
                     int *counter, int line_number, int *bool_flag_l) {
  int coincidence = 0;
  for (int i = 1; i < argc; i++) {
    char *search;
    int num = 0;
    if (t_or_f[i].status == 1 || t_or_f[i].status == 2) {
      if (t_or_f[i].status == 1) search = argv[i];
      if (t_or_f[i].status == 2) search = &(argv[i][t_or_f[i].position_ef + 1]);

      coincidence = comparison(all_flags[1].status, all_flags[9].status, text,
                               search, &num);
      if (coincidence && !all_flags[2].status) {
        print_grep(counter, t_or_f, all_flags, name_file, line_number, text,
                   bool_flag_l, search, num);
        i = argc;
      } else if (coincidence && all_flags[2].status)
        i = argc;

    } else if (t_or_f[i].status == 4 || t_or_f[i].status == 5) {
      char *template_file;
      if (t_or_f[i].status == 4) template_file = argv[i];
      if (t_or_f[i].status == 5)
        template_file = &(argv[i][t_or_f[i].position_ef + 1]);
      FILE *fp_f = fopen(template_file, "r");
      int ext = 0;
      if (fp_f) {
        char ch = getc(fp_f);
        while (ch != EOF && !ext) {
          char search_f[10024] = {'\0'};
          file_line(fp_f, search_f, &ch);
          num = 0;
          coincidence = comparison(all_flags[1].status, all_flags[9].status,
                                   text, search_f, &num);
          if (coincidence && !all_flags[2].status) {
            print_grep(counter, t_or_f, all_flags, name_file, line_number, text,
                       bool_flag_l, search_f, num);
            ext = 1;
          } else if (coincidence && all_flags[2].status)
            ext = 1;

          if (ch != EOF) ch = getc(fp_f);
        }
      }
      fclose(fp_f);
    }
    if (all_flags[2].status && i + 1 == argc && !coincidence)
      print_grep(counter, t_or_f, all_flags, name_file, line_number, text,
                 bool_flag_l, search, num);
    search = NULL;
  }
}

void print_grep(int *counter, struct template_or_file *t_or_f,
                struct flags *all_flags, char *name_file, int line_number,
                char *text, int *bool_flag_l, char *search, int num) {
  *counter += 1;
  if (!all_flags[4].status) {
    if (t_or_f[0].status >= 2 && !all_flags[3].status && !all_flags[6].status)
      printf("%s:", name_file);
    if (all_flags[5].status && !all_flags[3].status) printf("%d:", line_number);
    if (!all_flags[3].status && (!all_flags[9].status || all_flags[2].status))
      printf("%s\n", text);
    else if (all_flags[9].status && !all_flags[3].status)
      printf("%s\n", search);
    for (int i = 1; !all_flags[3].status && all_flags[9].status && i < num; i++)
      printf("%s\n", search);
  } else {
    *bool_flag_l = 1;
  }
}

int comparison(int flag_i, int flag_o, char *text, char *search, int *num) {
  int answer = 0;
  char array_text[strlen(text) + 1];
  char array_search[strlen(search) + 1];
  int flag = 0;
  if (flag_i) flag = 1;
  case_change(array_text, text, flag);
  case_change(array_search, search, flag);
  char *entry = array_text;

  do {
    entry = strstr(entry, array_search);
    if (entry) answer = 1;

    if (flag_o && entry) {
      entry += strlen(search);
      *num += 1;
    }
  } while (flag_o && entry && strlen(entry) > strlen(search));
  entry = NULL;
  return answer;
}

void case_change(char *array, char *text, int flag) {
  int i;
  for (i = 0; i < (int)strlen(text); i++) {
    if (text[i] >= 65 && text[i] <= 90 && flag)
      array[i] = text[i] + 32;
    else
      array[i] = text[i];
  }
  array[i] = '\0';
}

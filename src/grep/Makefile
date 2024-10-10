CC = gcc
FLAG = -Wall -Werror -Wextra

s21_grep :
	$(CC) $(FLAG) main.c s21_grep_lib.c -o s21_grep
test : 
	sh test_func_grep.sh

clean :
	rm s21_grep
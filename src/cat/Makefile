CC = gcc
FLAG = -Wall -Werror -Wextra

s21_cat :
	$(CC) $(FLAG) main.c s21_cat_lib.c -o s21_cat

test :
	sh test_bash.sh

rebuild :
	make clean
	make s21_cat

clean :
	rm s21_cat
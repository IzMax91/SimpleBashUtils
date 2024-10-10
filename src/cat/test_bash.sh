#!/bin/bash

all_flags1=(b e n s t v)
all_flags2=(-b -e -n -s -t -v)
test_file=New.txt
flag1=""
flag2=""
var1=0
FAIL=0

while [ $var1 \< 6 ]
do
dopflag=$[ $var1 + 1 ]
if [ $dopflag \> 5 ] ; then
    dopflag=0
fi

flag1=${all_flags1[$var1]}
flag2=${all_flags2[$var1]}
var2=0

while [ $var2 \< 6 ]
do

i=0
while [ $i \< 2 ]
do
answer=""
if [ $i = 0 ] ; then
    ./s21_cat -$flag1 $test_file >> file1.txt
    cat -$flag1 $test_file >> file2.txt
    answer="-"
    answer+=$flag1
elif [ $var2 != 0 ] ; then
    ./s21_cat $flag2 $test_file >> file1.txt
    cat $flag2 $test_file >> file2.txt
    answer=$flag2
else
    i=$[ $i + 1]
    continue
fi

if cmp -s file1.txt file2.txt ; then
    echo "\033[32mSUCCESS\033[0m: test_file - $test_file: flags $answer"
else
    echo "\033[31mFAIL\033[0m: $answer"
    FAIL=$[ $FAIL +1 ]
fi
> file1.txt
> file2.txt
i=$[ $i + 1]
done


flag1+=${all_flags1[dopflag]}
flag2+=" "
flag2+=${all_flags2[dopflag]}

dopflag=$[ $dopflag + 1]
if [ $dopflag \> 5 ]
    then
    dopflag=0
fi

var2=$[ $var2 + 1 ]
done
var1=$[ $var1 + 1 ]
done

rm file1.txt
rm file2.txt
echo "\033[31mFAIL\033[0m - $FAIL"
#!/bin/bash

GREEN='\e[32m'
NC='\e[0m'
RED='\e[31m'
EXE=s21_cat.c

printf "${GREEN}-----RUNNING TESTS-----${NC}\n"

cat JustTest.txt >a
gcc $EXE -lm && ./a.out JustTest.txt >b
result=$(diff a b)
failed=0
i=1

# TEST 1
if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 2
cat -b JustTest.txt >a
gcc $EXE -lm && ./a.out -b JustTest.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 3
cat -n JustTest.txt >a
gcc $EXE -lm && ./a.out -n JustTest.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 4
cat -s JustTest.txt >a
gcc $EXE -lm && ./a.out -s JustTest.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 5
cat -t JustTest.txt >a
gcc $EXE -lm && ./a.out -t JustTest.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 6
cat -e JustTest.txt >a
gcc $EXE -lm && ./a.out -e JustTest.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 7
FILE=JustTest.txt
FLAGS=-e
cat $FLAGS $FILE >a
gcc $EXE -lm && ./a.out $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 8
FILE=JustTest.txt
FLAGS=-b
cat $FLAGS $FILE >a
gcc $EXE -lm && ./a.out $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 9
FILE=JustTest.txt
FLAGS=-n
cat $FLAGS $FILE >a
gcc $EXE -lm && ./a.out $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 10
FILE=JustTest.txt
FLAGS=-s
cat $FLAGS $FILE >a
gcc $EXE -lm && ./a.out $FLAGS $FILE >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 11
cat -b JustTest.txt >a
gcc $EXE -lm && ./a.out --number-nonblank JustTest.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 12
cat -n JustTest.txt >a
gcc $EXE -lm && ./a.out --number JustTest.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

((i++))

# TEST 13
cat -s JustTest.txt >a
gcc $EXE -lm && ./a.out --squeeze-blank JustTest.txt >b
result=$(diff a b)

if [ $? -eq 0 ]; then
    printf " TEST #$i ${GREEN}PASSED${NC}\n"
else
    printf " TEST #$i ${RED}FAILED${NC}\n"
    printf "$result"
    ((failed++))
fi

printf " ${GREEN}-----DONE $((i - failed))/$((i))-----${NC}\n"

rm a.out a b

#!/bin/bash

assert_equals () {
  if [ "$1" = "$2" ]; then
    echo -e "$Green $Check_Mark Success $Color_Off"
  else
    echo -e "$Red Failed $Color_Off"
    echo -e "$Red Expected -$1- to equal -$2- $Color_Off"
    Errors=$((Errors  + 1))
    exit 1
  fi
}

response=$(./calc "e 4 + 2")
assert_equals "$response" 6

response=$(./calc "e 5 - 2")
assert_equals "$response" 3

response=$(./calc "e -6 - -2")
assert_equals "$response" -4

response=$(./calc "b 111 + 1")
assert_equals "$response" 1000

response=$(./calc "e 111 - 1")
assert_equals "$response" 110

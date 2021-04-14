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

response=$(./calc "e -3 + 188")
assert_equals "$response" 185

response=$(./calc "e 5 - 2")
assert_equals "$response" 3

response=$(./calc "e 3 - 9")
assert_equals "$response" -6

response=$(./calc "e -6 - -2")
assert_equals "$response" -4

response=$(./calc "e 111 + 111")
assert_equals "$response" 1110

response=$(./calc "e -111 + 1000")
assert_equals "$response" 1

response=$(./calc "e 1010 - 111")
assert_equals "$response" 11

response=$(./calc "e 100 - 1110")
assert_equals "$response" -1010

response=$(./calc "e -1110 - -111")
assert_equals "$response" -111

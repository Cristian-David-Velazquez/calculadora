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

response=$(./calc "e 2 + 2")
assert_equals "$response" Bienvenido a la calculadora de SisCom de Octa y Cristian

Aqui se puede sumar o restar enteros o binarios
Ingresa la operacion separando los sumando por espacios o "fin" para salir
Ingrese antes de la operacion e para enteros o b para binarios
ejemplo: b 1000 + 1111

--------------------

Operación: e 2 + 2
Resultado: 4
4

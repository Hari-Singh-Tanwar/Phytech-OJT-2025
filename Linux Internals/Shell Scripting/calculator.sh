#!/bin/bash

read -p "Enter first number:  " a
read -p "Enter second number: " b

read -p "Enter operation you want to perform. +, -, x, / or % : " op

case "$op" in
  "+")
    echo "$a + $b = $((a+b))"
    ;;
  "-")
    echo "$a - $b = $((a-b))"
    ;;
  "x")
    echo "$a x $b = $((a*b))"
    ;;
  "/")
    echo "$a / $b = $((a/b))"
    ;;
  "%")
    echo "$a % $b = $((a%b))"
    ;;
  *)
    echo "Enter correct command."
    ;;
esac

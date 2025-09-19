#!/bin/bash

is_armstrog()
{

  local num=$1
  local len=${num}
  local temp=$num
  local sum=0

  while [ $temp -gt 0 ]; do
    digit=$((temp%10))
    power=1
    for ((i=1; i<= len; i++)); do
      power=$((power*digit))
    done
    sum=$((sum + power))
    temp=$((temp/10))
  done

  if [ $sum -eq $num ]; then
    return 0 # ture
  else
    return 1 # false
  fi
}

read -p "Enter a number: " n

if  is_armstrog $n; then
  echo "$n is a armstrong number."
else
  echo "$n is not armstrong number."
fi

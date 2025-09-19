#!/bin/bash

echo "Check if entered number is a armstromg number or not"
read -p "Enter a number: " num

org=$num
sum=0
num_dig=${#num}

if [[ ! $number =~ ^[0-9]+$ ]]; then
    echo "Please enter a valid positive integer."
    exit 1
fi

temp=$num

while [ temp -gt 0 ]; do
  digit=$((temp % 10))
  pow=1
  for ((i=1 ; i<=$digit ; i++))do
    pow=$((pow * digit))
  done

  sum=$((sum + pow))
  temp=$((temp/10))
done

if [ $sum -eq $org ]; then
  echo "$org is a armstrong number"
else
  echo "$org is NOT a armstrong number"
fi

#!/bin/bash

echo "Check if entered number is palindome or not."

read -p "Ener a number: " num

rev_num=0
org_num=$num

while [ $num -gt 0 ]; do
  last_dig=$((num%10))
  rev_num=$((rev_num * 10 + last_dig))
  num=$((num / 10))
done

if [ $org_num -eq $rev_num ]; then
  echo "$org_num is palindome number."
else
  echo "$org_num is NOT a palindome number"
fi

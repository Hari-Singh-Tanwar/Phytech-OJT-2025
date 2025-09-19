#!/bin/bash

echo "Check entered character is vowel or consonant"
read -p "Enter a character: " char

if [ "$char" == "a" ] || [ "$char" == "e" ] || [ "$char" == "i" ] || [ "$char" == "o" ] || [ "$char" == "u" ]; then
  echo "$char is a vowel"
else
  echo "$char is consonanat"
fi 

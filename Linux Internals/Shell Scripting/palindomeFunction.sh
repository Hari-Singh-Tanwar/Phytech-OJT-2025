#!/bin/bash

is_palindome() {
    local num=$1
    local rev_num=0

    while [ $num -gt 0 ]; do
        local last_dig=$((num % 10))
        rev_num=$((rev_num * 10 + last_dig))
        num=$((num / 10))
    done

    if [ $1 -eq $rev_num ]; then
        return 0  # It's a palindrome
    else
        return 1  # Not a palindrome
    fi
}

read -p "Enter a number: " num

if is_palindome "$num"; then
    echo "$num is a palindrome."
else
    echo "$num is not a palindrome."
fi
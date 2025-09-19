#!/bin/bash
swap(){
    local a=$1
    local b=$2
    echo "Before swapping: a=$a, b=$b"
    local temp=$a
    a=$b
    b=$temp
    echo "After swapping: a=$a, b=$b"
}

echo "Swapping two numbers"
read -p "Enter first number: " num1
read -p "Enter second number: " num2
swap "$num1" "$num2"
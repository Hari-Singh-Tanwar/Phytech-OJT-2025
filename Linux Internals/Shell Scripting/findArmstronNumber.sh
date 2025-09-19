#!/bin/bash

# Function to check if a number is an Armstrong number
is_armstrong() {
    num=$1
    len=${#num}
    sum=0
    temp=$num

    while [ $temp -gt 0 ]; do
        digit=$((temp % 10))
        power=1
        for ((i=1; i<=len; i++)); do
            power=$((power * digit))
        done
        sum=$((sum + power))
        temp=$((temp / 10))
    done

    if [ $sum -eq $num ]; then
        return 0  # True, is an Armstrong number
    else
        return 1  # False, not an Armstrong number
    fi
}

# Main script
start=1
end=10000
count=0

echo "Armstrong numbers between $start and $end are:"
for ((num=start; num<=end; num++)); do
    if is_armstrong $num; then
        echo $num
        ((count++))
    fi
done

echo "Total number of Armstrong numbers found: $count"

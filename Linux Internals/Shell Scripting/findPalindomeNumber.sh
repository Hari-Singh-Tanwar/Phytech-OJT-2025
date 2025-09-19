#!/bin/bash

# Function to check if a number is a palindrome
is_palindrome() {
    num=$1
    # Convert number to string for easy comparison
    str_num="$num"
    # Reverse the string
    reverse=$(echo "$str_num" | rev)
    
    if [ "$str_num" = "$reverse" ]; then
        return 0  # True, is a palindrome
    else
        return 1  # False, not a palindrome
    fi
}

# Main script
start=1
end=10000
count=0

echo "Palindrome numbers between $start and $end are:"
for ((num=start; num<=end; num++)); do
    if is_palindrome $num; then
        echo $num
        ((count++))
    fi
done

echo "Total number of palindrome numbers found: $count"

#!/bin/bash
###################################################################################################################
#Author : Nidhi Goswami
#Created : 21-01-2026
#Discription :script to take two numbers as input and perform addition, subtraction, multiplication, and division.
###################################################################################################################
source ../lib/validate_number.sh
source ../lib/functions.sh
source ../lib/continue_exit.sh

while true
do
    while true
    do
        echo "Enter the first number:"
        read num1
        if validate_number "$num1" "num1"; then
            break
        fi
    done


    while true
    do
        echo "Enter the second number:"
        read num2
        if validate_number "$num2" "num2"; then
            break
        fi
    done

    echo "Add:$(add $num1 $num2)"
    echo "sub:$(sub $num1 $num2)"
    echo "mul:$(mul $num1 $num2)"
    echo "div :$(div $num1 $num2)"

    if is_very_large "$num1" || is_very_large "$num2"; then
    echo "garbage values"
    continue
    fi

    if ! continue_or_exit; then
        echo "end"
        break
    fi
done


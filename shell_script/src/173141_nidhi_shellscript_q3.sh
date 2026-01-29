#!/bin/bash

#Author : Nidhi Goswami
#Date : 22-01-2026
#Discription : Find the Largest number from 3 number

source ../lib/validate_number.sh
source ../lib/functions.sh
source ../lib/continue_exit.sh


while true
do
    while true
    do
        read -p "Enter first number: " n1
        if validate_number "$n1"; then
            break
        else
            echo "No.1 Invalid"
        fi
    done

    while true
    do
        read -p "Enter second number: " n2
        if validate_number "$n2"; then
            break
        else
            echo "num2 is not a valid number"
        fi
    done

    while true
    do
        read -p "Enter third number: " n3
        if validate_number "$n3"; then
            break
        else
            echo "num3 is not a valid number"
        fi
    done

    limit=10000
    if (( n1 > limit || n2 > limit || n3 > limit )); then
        echo "Cannot process large no."
        if ! continue_or_exit; then
            echo "Done"
            break
        fi
        continue
    fi

    largest=$(find_largest "$n1" "$n2" "$n3")
    echo "The largest number is $largest"

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done


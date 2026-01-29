#!/bin/bash

################################################
#Author : Nidhi Goswami
#created :21-01-2026
#Discription : Check the number is even of odd 
################################################

source ../lib/validate_number.sh
source ../lib/functions.sh
source ../lib/continue_exit.sh

while true
do
    while true
    do
        echo "Enter a number:"
        read input

        validation_output=$(validate_number "$input" "Input")
        
        if [ $? -eq 0 ]; then
            num="$validation_output" 
            break   
        else
            echo "$validation_output" 
        fi
    done

    result=$(check_even_odd "$num")
    echo "$input is $result"

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done

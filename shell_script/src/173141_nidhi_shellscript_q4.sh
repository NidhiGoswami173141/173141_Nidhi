#!/bin/bash

#Author:Nidhi Goswami
#Date: 23-01-2026
#Discription : script to check if a given string is a palindrome.


source ../lib/functions.sh
source ../lib/validate_number.sh
source ../lib/continue_exit.sh

while true
do
    echo -n "Enter a string: "
    read user_input

    validate_input "$user_input"
    if [ $? -ne 0 ]; then
        continue
    fi

    check_palindrome "$user_input"

    if ! continue_or_exit; then
    break
    fi
done

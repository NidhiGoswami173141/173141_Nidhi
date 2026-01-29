#!/bin/bash

#Author : Nidhi Goswami
#Date : 26-01-2026
#Description :generate random password for length 

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true
do
    read -p "Enter the password length: " length

    generate_random_password "$length"

    if ! continue_or_exit; then
        break
    fi
done


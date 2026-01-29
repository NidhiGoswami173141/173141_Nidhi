#!/bin/bash

#Author : Nidhi Goswami
#Date : 26-01-2026
#Discription : check that size a specified directory 

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true
do
    read -p "Enter the directory path to check: " dir

    # TRIM spaces
    dir="$(echo "$dir" | xargs)"

    # EXPAND ~
    dir=$(eval echo "$dir")

    check_directory_size "$dir"

    if ! continue_or_exit; then
        break
    fi
done


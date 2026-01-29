#!/bin/bash

#Author : Nidhi Goswami
#Date : 26-01-2026
#Discription: Recursivefile search

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true
do
    read -p "Enter the file name to search for: " filename
    read -p "Enter the directory to search: " directory

    search_file_recursive "$filename" "$directory"

    if ! continue_or_exit; then
        break
    fi
done


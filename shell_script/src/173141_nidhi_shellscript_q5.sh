#!/bin/bash

#Author : Nidhi Goswami
#Date : 23-01-2026
#Discription : script that takes a directory as input, creates a backup of all .txt files, and stores them in a compressed archive with the current date as the filename.

source ../lib/continue_exit.sh

while true; do
    echo "Enter directory or path:"
    read path
    path="$(echo "$path" | xargs)"
    path=$(eval echo "$path")

    backup_file="$HOME/backup_$(date +%Y-%m-%d).tar.gz"

    if [[ "$path" == *.txt ]]; then
        echo "this $(basename "$path") file not found"
        continue
    fi


    if [[ ! -d "$path" ]]; then
        echo "this $path directory not found"
        continue
    fi


    count=$(find "$path" -type f -iname "*.txt" | wc -l)

    if [[ "$count" -eq 0 ]]; then
        echo "Folder does not contain any txt files"
        continue
    fi

    tar -czf "$backup_file" -C "$path" $(find "$path" -type f -iname "*.txt" -printf "%P ")

    echo "filename: $(basename "$backup_file") in home directory"


    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done


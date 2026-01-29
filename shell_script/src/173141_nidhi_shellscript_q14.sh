#!/bin/bash

#Author: Nidhi Goswami
#Date : 26-01-2026
#Description : script to count the number of occurrences of each word in a given text file, sorted by frequency.

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true; do
    echo -n "Enter the text file path: "
    read input_path

    file=$(eval echo $input_path)

    if check_errors "$file"; then
        count_words "$file"
    fi

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done


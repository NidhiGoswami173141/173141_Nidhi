#!/bin/bash

# Author : Nidhi Goswami
# Date   : 26-01-2026
# Description : log file for any c program

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true
do
    echo "Enter c program file path:"
    read cfile

    process_c_file "$cfile"

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done


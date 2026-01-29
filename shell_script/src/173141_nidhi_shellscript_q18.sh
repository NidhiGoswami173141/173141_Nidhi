#!/bin/bash

# Author : Nidhi Goswami
# Date   : 26-01-2026
# Description : check .c file as input and check coding standard are applied

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true
do
    echo "Enter c file path:"
    read cfile

    check_coding_standards "$cfile"

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done 

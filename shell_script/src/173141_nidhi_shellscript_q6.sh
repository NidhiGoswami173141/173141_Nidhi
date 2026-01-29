#!/bin/bash

#Author : Nidhi Goswami
#Date : 26-01-2026
# Discription : Process monitoring Script 

source ../lib/functions.sh
source ../lib/continue_exit.sh


while true
do
    echo "Enter the process name to check:"
    read pname

    check_process "$pname"

    if ! continue_or_exit; then
    break
    fi
done


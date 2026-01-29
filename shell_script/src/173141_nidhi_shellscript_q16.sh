#!/bin/bash

# Author : Nidhi Goswami
# Date   : 26-01-2026
# Description : Script to read kernel log file

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true
do
    read -p "Enter Input1: " IN1
    read -p "Enter Input2: " IN2

 
    if [[ -z "$IN1" && -z "$IN2" ]]; then
        echo "cannot take empty i/p"
    else
        [[ -n "$IN1" ]] && process_input "$IN1"
        [[ -n "$IN2" ]] && process_input "$IN2"
    fi

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done



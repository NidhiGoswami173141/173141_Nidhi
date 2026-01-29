#!/bin/bash

#Author: Nidhi Goswami
#Date : 26-01-2026
#Discription : add new user to a system and set default passwords 


source ../lib/functions.sh
source ../lib/continue_exit.sh

if ! is_root; then
    echo "Run script in root mode"
    exit 1
fi

while true; do
    read -p "Enter the username to add: " u
    add_user "$u"

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done


#!/bin/bash

#Author : Nidhi Goswami
#Date : 26-01-2026
#Discription : file globing

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true; do
    read -p "Enter linux username: " user_input
    read -p "Enter GID: " gid_input
    read -p "Enter firstname: " fname_input
    read -p "Enter taskid (TaskName): " tid_input


    process_task "$user_input" "$gid_input" "$fname_input" "$tid_input"

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done


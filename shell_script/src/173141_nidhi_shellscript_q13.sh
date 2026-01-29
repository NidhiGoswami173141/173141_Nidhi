#!/bin/bash

#Author : Nidhi Goswami 
#Date : 26-01-2026
#Description : Script that tracks and logs user logins and logout events , appending to the data to a log file.

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true; do
    read -p "Enter the log file path: " log_path
    log_path=$(eval echo "$log_path")

    validate_input "$log_path" || continue
    validate_extension "$log_path" || continue
    validate_path "$log_path" || continue

    track_login "$log_path"

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done


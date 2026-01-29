#Author : Nidhi Goswami
#Date : 26-01-2026
#Description : Script for generate a disk usage report for all mounted file systems and save it to a file 


#!/bin/bash

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true; do
    read -p "Enter the output file to save the disk usage report: " outfile

    generate_disk_report "$outfile"

    if ! continue_or_exit; then
        echo "Done"
        break
    fi
done


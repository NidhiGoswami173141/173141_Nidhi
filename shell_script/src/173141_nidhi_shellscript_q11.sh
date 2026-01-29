#!/bin/bash

# Author: Nidhi Goswami
# Date:26-01-2026
# Description: System resource monitoring

source ../lib/functions.sh
source ../lib/continue_exit.sh

while true
do
    read -p "Enter CPU usage threshold (0-100): " cpu
    read -p "Enter Memory usage threshold (0-100): " mem

    monitor_system_resources "$cpu" "$mem"

    if ! continue_or_exit; then
        break
    fi
done


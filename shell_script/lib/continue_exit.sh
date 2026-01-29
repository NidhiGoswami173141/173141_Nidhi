#!/bin/bash

continue_or_exit() {
    echo "Do you want to continue? (y/n)"
    read choice

    if [ "$choice" = "y" ] || [ "$choice" = "Y" ]
    then
        return 0
    else
        return 1
    fi
}

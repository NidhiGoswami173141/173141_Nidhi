#!/bin/bash

validate_number() {
    local input="$1"

    # blank input
    if [[ -z "$input" ]]; then
        echo "Not a valid number"
        return 1
    fi

    # integer (positive or negative)
    if [[ "$input" =~ ^-?[0-9]+$ ]]; then
        echo "$input"
        return 0
    fi

    # number ending with .0 (like 6.0, -8.0)
    if [[ "$input" =~ ^-?[0-9]+\.0$ ]]; then
        echo "${input%.0}"
        return 0
    fi

    # float like 5.5
    if [[ "$input" =~ ^-?[0-9]+\.[0-9]+$ ]]; then
        echo "float is not valid"
        return 1
    fi

    if [[ -z "$value" ]]; then
        echo "This is a empty string"
        return 1
    fi

    trimmed=$(echo "$value" | tr -d ' ')

    if [[ -z "$trimmed" ]]; then
        echo "cannot enter empty string"
        return 1
    fi

    # anything else
    echo "Not a valid number"
    return 1
}



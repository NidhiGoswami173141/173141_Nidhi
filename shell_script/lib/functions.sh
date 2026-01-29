
#!/bin/bash

####################################################################################
#Author : Nidhi Goswami 
#Created : 21-01-2026
####################################################################################

is_empty() {
    [[ -z "$1" ]]
}


####################################################################################################
#Q1 - function for addition , multiplication , substration and division
####################################################################################################

add() { echo "$1 + $2" | bc; }
sub() { echo "$1 - $2" | bc; }
mul() { echo "$1 * $2" | bc; }

div() {
    local n1=$1
    local n2=$2

    if [ "$n1" -eq 0 ] && [ "$n2" -eq 0 ]; then
        echo "div : undefined"
    elif [ "$n2" -eq 0 ]; then
        echo "div : can not divide by zero instead error"
    else
        echo "scale=1; $n1 / $n2" | bc
    fi
}
is_very_large() {
    local num=${1%.*}
    (( num > 1000000 ))
}

############################################################################
#Q2 - for checking number is even or odd
############################################################################
check_even_odd() {
    local n="$1"
    if [[ "$n" == *.0 ]]; then
        n="${n%.0}"
    fi
    if (( n % 2 == 0 )); then
        echo "Even number"
    else
        echo "Odd number"
    fi
}



############################################################################
#Q3 for check which number is greater than 3 number 
############################################################################

find_largest() {
    a=$1
    b=$2
    c=$3

    largest=$a

    if (( $(echo "$b > $largest" | bc -l) )); then
        largest=$b
    fi

    if (( $(echo "$c > $largest" | bc -l) )); then
        largest=$c
    fi

    echo "$largest"
}


###########################################
#Q4 String is pelindrome or not
###########################################

validate_input() {
    value="$1"

    if [ -z "$value" ]; then
        echo "Input cannot be empty."
        return 1
    else
        return 0
    fi
}

check_palindrome() {
    input="$1"
    lower_input=$(echo "$input" | tr 'A-Z' 'a-z')

    processed=$(echo "$lower_input" | tr -d ' ')

    reversed=$(echo "$processed" | rev)

    if [ "$processed" = "$reversed" ]; then
        echo "The string '$input' is a palindrome."
    else
        echo "The string '$input' is not a palindrome."
    fi
}


###########################################
#q6 script for  process monitoring 
###########################################
check_process() {
    local name="$1"

    if [[ -z "$name" ]]; then
        echo "invalid input"
        return
    fi

    if [[ "$name" =~ [[:space:]] ]]; then
        echo "not running process"
        return
    fi

    if [[ "$name" =~ ^[0-9]+$ ]]; then
        if ps -p "$name" > /dev/null 2>&1; then
            echo "$name is running"
        else
            echo "$name is not running"
        fi
        return
    fi

    if ps -e | grep -i -w "$name" > /dev/null; then
        echo "$name is running"
    else
        echo "$name is not running"
    fi
}

##################################
# Task 7: User Management
##################################
is_root() {
    [ "$EUID" -eq 0 ]
}

user_exists() {
    id "$1" &>/dev/null
}

add_user() {
    local user="$1"

    user="$(echo "$user" | xargs)"

    if [[ -z "$user" ]]; then
        echo "Username cannot be empty"
        exit 1
    fi

    if [[ "$user" =~ [[:space:]] ]]; then
        echo "Username cannot contain spaces"
        exit 1
    fi

    if user_exists "$user"; then
        echo "User already exists"
        exit 1
    fi

    useradd "$user"
    echo "$user:password123" | chpasswd

    echo "User '$user' has been added successfully with default password 'password123'."
}

##################################
# Task 8: Directory Size Check
##################################

check_directory_size() {
    local input="$1"
    local limit=100

    if [[ -z "$input" ]]; then
        echo "invalid input"
        return
    fi

    path=$(eval echo "$input")

    if [[ ! -e "$path" ]]; then
        echo "this $input dirctory not found"
        return
    fi

    if [[ ! -r "$path" ]]; then
        echo "permission denied"
        return
    fi

    if [[ -f "$path" ]]; then
        size=$(du -sm "$path" 2>/dev/null | cut -f1)

        if [[ "$size" -gt "$limit" ]]; then
            echo "The size of the directory $input is ${size}MB. The size exceeds the ${limit}MB limit!"
        else
            echo "The size of the directory $input is ${size}MB. The size is within the 100MB limit."
        fi
        return
    fi

    if [[ -d "$path" ]]; then
        size=$(du -sm "$path" 2>/dev/null | cut -f1)

        if [[ "$size" -gt "$limit" ]]; then
            echo "The size of the directory $input is ${size}MB. The size exceeds the ${limit}MB limit!"
        else
            echo "The size of the directory $input is ${size}MB. The size is within the 100MB limit."
        fi
        return
    fi
}



##################################
# Task 9: Recursive File Search
##################################

search_file_recursive() {
    local filename="$1"
    local directory="$2"

    if [[ -z "$filename" ]]; then
        echo "file name cannot be empty"
        return
    fi

    if [[ -z "$directory" ]]; then
        echo "dirctory name can not be empty"
        return
    fi


    directory=$(eval echo "$directory")


    if [[ ! -d "$directory" ]]; then
        echo "the dirctory $directory does not extits"
        return
    fi

    result=$(find "$directory" -type f -name "$filename" 2>/dev/null)

    if [[ -z "$result" ]]; then
        echo "file $filename not found in $directory"
    else
        echo "Found $filename at:"
        echo "$result"
    fi
}


##################################
# Task 10: Random Password Generator
##################################
generate_random_password() {
    local length="$1"

    if is_empty "$length"; then
        echo "Password length cannot be empty."
        return 1
    fi

    if ! [[ "$length" =~ ^-?[0-9]+$ ]]; then
        echo "invalid input provided this is a not numeric value"
        return 1
    fi

    if [[ "$length" -lt 0 ]]; then
        echo "Password length must be positive value"
        return 1
    fi

    if [[ "$length" -eq 0 ]]; then
        echo "password length must be  greater than 0."
        return 1
    fi

    local chars='A-Za-z0-9@#$%^&*'
    local password
    password=$(tr -dc "$chars" </dev/urandom | head -c "$length")

    echo "Generated password : length $length"
    echo "$password"
}

#######################################################

#Q11 - System resource monitoring 
######################################################
LOG_FILE="system_monitor.log"

is_number() {
    [[ "$1" =~ ^[0-9]+([.][0-9]+)?$ ]]
}

get_cpu_usage() {
    read cpu u n s i iw ir sir st g gn < /proc/stat
    total1=$((u+n+s+i+iw+ir+sir+st))
    idle1=$i
    sleep 1
    read cpu u n s i iw ir sir st g gn < /proc/stat
    total2=$((u+n+s+i+iw+ir+sir+st))
    idle2=$i
    total=$((total2 - total1))
    idle=$((idle2 - idle1))
    echo $(( (100 * (total - idle)) / total ))
}

get_memory_usage() {
    read total used free <<< $(free -m | awk '/Mem:/ {print $2,$3,$4}')
    echo $(( used * 100 / total ))
}

monitor_system_resources() {

    cpu_limit="$1"
    mem_limit="$2"

    if is_empty "$cpu_limit"; then
        echo "CPU usage threshold cannot be empty."
        return 1
    fi

    if is_empty "$mem_limit"; then
        echo "Memory usage threshold cannot be empty."
        return 1
    fi

    if ! is_number "$cpu_limit"; then
        echo "invalid input provided this is a not numeric value for cpu"
        return 1
    fi

    if ! is_number "$mem_limit"; then
        echo "invalid input provided this is not a numeric value for memory"
        return 1
    fi

    if (( $(echo "$cpu_limit < 0" | bc -l) )); then
        echo "CPU usage threshold cannot be negetive."
        return 1
    fi

    if (( $(echo "$mem_limit < 0" | bc -l) )); then
        echo "Memory usage threshold cannot be negetive."
        return 1
    fi

    if (( $(echo "$cpu_limit > 100 || $mem_limit > 100" | bc -l) )); then
        echo "cannot be beyond 100%"
        return 1
    fi

    cpu=$(get_cpu_usage)
    mem=$(get_memory_usage)

    if (( cpu > cpu_limit )); then
        echo "CPU usage is $cpu%. Exceeds threshold of $cpu_limit%."
        echo "$(date): CPU $cpu% > $cpu_limit%" >> "$LOG_FILE"
    else
        echo "CPU usage is $cpu%. Within threshold."
        echo "$(date): CPU OK $cpu%" >> "$LOG_FILE"
    fi

    if (( $(echo "$mem > $mem_limit" | bc -l) )); then
        echo "Memory usage is $mem%. Exceeds threshold of $mem_limit%."
        echo "$(date): Memory $mem% > $mem_limit%" >> "$LOG_FILE"
    else
        echo "Memory usage is $mem%. Within threshold."
        echo "$(date): Memory OK $mem%" >> "$LOG_FILE"
    fi
}


###################################################################################################
#Q12 - Functions generates a disk usage report for all mounted file systems and saves it to a file.
###################################################################################################

generate_disk_report() {
    local outfile="$1"


    if [ -z "$outfile" ]; then
        echo "Output path cannot be empty"
        return 1
    fi

    outfile="${outfile/#\~/$HOME}"

    case "$outfile" in
        *.txt) ;;
        *)
            echo "Not valid file path. Enter a .txt file"
            return 1
            ;;
    esac

    dirpath=$(dirname "$outfile")
    if [ ! -d "$dirpath" ]; then
        echo "Invalid file path"
        return 1
    fi

    if [ -f "$outfile" ]; then
        echo "Disk usage report file exists, overriding the data"
    else
        echo "File created. Disk usage report will be saved"
    fi

    df -h > "$outfile"
    echo "Disk usage report generated and saved to $outfile"
}



######################################
#q13 function to track login/logout
######################################

validate_input() {
    if [ -z "$1" ]; then
        echo "Output file path cannot be empty"
        return 1
    fi
}


validate_extension() {
    if [[ "$1" != *.log ]]; then
        echo "Enter valid file type (.log)"
        return 1
    fi
}

validate_path() {
    dir=$(dirname "$1")

    mkdir -p "$dir" 2>/dev/null

    if [ ! -d "$dir" ]; then
        echo "Invalid file path"
        return 1
    fi
}

LOG_FILE=""

track_login() {
    LOG_FILE="$1"

    if [ -f "$LOG_FILE" ]; then
        echo "Overwriting existing data"
        > "$LOG_FILE"
    fi

    echo "$(date): User logged in" >> "$LOG_FILE"

    trap 'echo "$(date): User logged out" >> "$LOG_FILE"' EXIT

    echo "User login tracking started."
    echo "Data saved to $LOG_FILE"
}


#######################################
#q14 functions for count word 
#######################################

count_words() {
    local file=$1
    echo "Word frequency analysis:"

    grep -oE '\w+' "$file" | tr '[:upper:]' '[:lower:]' | sort | uniq -c | sort -nr | while read count word; do
        echo "$word - $count occurrences"
    done
}

check_errors() {
    local path=$1

    if [ -z "$path" ]; then
        echo "file path can not empty"
        return 1
    elif [[ "$path" != *.txt ]]; then
        echo "only .txt files are allowed"
        return 1
    elif [ ! -e "$path" ]; then
        echo "the file $path does not exits"
        return 1
    elif [ ! -r "$path" ]; then
        echo "cant read this file"
        return 1
    elif [ ! -s "$path" ]; then
        echo "the file $path is empty"
        return 1
    fi
    return 0
}


################################
#Q15-  File Globing
################################

process_task() {
    local uname=$1
    local gid=$2
    local fname=$3
    local tid=$4

    if [[ -z "$uname" || -z "$gid" || -z "$fname" || -z "$tid" ]]; then
        echo "All inputs (username, GID, firstname, task ID) are required."
        return 1
    fi

    if [[ ! "$gid" =~ ^[0-9]{1,6}$ ]]; then
        echo "Enter valid GID"
        return 1
    fi

    if [[ "$tid" == *" "* ]]; then
        echo "spaces not allowed in taskname use _"
        return 1
    fi

    local main_dir="${gid}_${fname}"
    local sub_folder="$tid"
    local file_name="${gid}_${fname}_${tid}_Module1_task1.c"

    if [[ -d "$main_dir" && -d "$main_dir/$sub_folder" ]]; then
        echo "directory already exists"
        return 1
    fi

    if [[ -d "$main_dir" && ! -d "$main_dir/$sub_folder" ]]; then
        echo "Folder exists making subfolders"
        mkdir -p "$main_dir/$sub_folder"
        touch "$main_dir/$sub_folder/$file_name"
        return 0
    fi

    mkdir -p "$main_dir/$sub_folder"
    touch "$main_dir/$sub_folder/$file_name"
    echo "$main_dir/$sub_folder/$file_name"
}





########################################################################
#Q16 - Read the Kernel log file to find the kernel panic , segmentation
########################################################################
LOG_FILE="/var/log/kern.log"

process_input() {
    local input="$1"

    local term
    term=$(echo "$input" | xargs)

    local lower_term
    lower_term=$(echo "$term" | tr '[:upper:]' '[:lower:]')

    if [[ "$lower_term" != "panic" && "$lower_term" != "segfault" ]]; then
        echo "there is no fault $term"
        return
    fi

    if [ -f "$LOG_FILE" ]; then
        grep -i "$term" "$LOG_FILE"
    else
        echo "[Note: $LOG_FILE not found, displaying simulated output for $term]"
        echo "Jan 26 10:00:00 kernel: [123.456] $term detected at address 0x0000"
    fi
}



##################################
#Q17 - og file for any c program.
##################################

process_c_file() {
    local cfile="$1"

    if [ -z "$cfile" ]; then
        echo "input cannot be empty"
        return 1
    fi

    cfile="${cfile/#\~/$HOME}"

    case "$cfile" in
        *.c) ;;
        *)
            echo "only .c file take as i/p"
            return 1
            ;;
    esac

    if [ ! -f "$cfile" ]; then
        echo "$(basename "$cfile") file does not exists"
        return 1
    fi

    if [ ! -s "$cfile" ]; then
        echo "that file in log file empty"
        return 1
    fi

    logfile="$(basename "$cfile" .c).log"

    gcc "$cfile" -o a
    ./a &> "$logfile"

    if [ -s "$logfile" ]; then
        echo "o/p stored in log file"
    else
        echo "input cannot be empty c file"
    fi
}


#####################################################################################
#Q18 - which takes .c file as input and checks whether coding standards are applied .
#####################################################################################

check_coding_standards() {
    local cfile="$1"

    if [ -z "$cfile" ]; then
        echo "c file cannot be empty input"
        return 1
    fi

    cfile="${cfile/#\~/$HOME}"

    case "$cfile" in
        *.c) ;;
        *)
            echo ".c files are allowed"
            return 1
            ;;
    esac

    if [ ! -f "$cfile" ]; then
        echo "$(basename "$cfile") does not exits"
        return 1
    fi

    if [ ! -s "$cfile" ]; then
        echo "this $(basename "$cfile") file empty"
        return 1
    fi

    code_lines=$(grep -vE '^\s*(//|/\*|\*/|\*)' "$cfile" | grep -v '^\s*$')

    if [ -z "$code_lines" ]; then
        echo "C file is not valid"
        return 1
    fi

    if grep -q "//" "$cfile"; then
        echo "// comments are not allowed, only multi line comments are allowed"
        return 1
    fi

    if grep -q "#include" "$cfile" && grep -q "main()" "$cfile"; then
        echo "this $cfile file follow coding standards"
    else
        echo "this $(basename "$cfile") file does not follow coding standards"
    fi
}


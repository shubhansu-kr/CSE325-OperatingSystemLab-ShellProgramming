# !/bin/bash

read -p "Enter a positive number : " num 

if [ $num -le 1 ] 
then 
    echo "Neither Prime Nor Composite"
else 
    count=0
    for((i = 1; i <= $num; i++))
    do 
        if [ $(($num % &i)) eq 0 ]
        then 
            count=$count + 1
        fi
    done

    if [ $count eq 2 ]
    then 
        echo "$num is Prime"
    else 
        echo "$num is not Prime"
    fi 
fi 
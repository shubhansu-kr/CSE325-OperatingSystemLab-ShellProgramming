# !/bin/bash

echo "---------Print Primes---------"
read -p "Enter UpperLimit: " limit

for ((num=2; num <= $limit; num++))
do 
    count=0
    for((i = 1; i <= $num; i++))
    do 
        if [ $(($num % $i)) -eq 0 ]
        then 
            count=$(($count + 1))
        fi
    done

    if [ $count -eq 2 ]
    then 
        echo "$num"
    fi 

done 

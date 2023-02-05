# !/bin/bash

echo "---------Multiplication Table--------"

read -p "Enter num: " num 

echo ""
for i in {1..10}
do 
    echo "$num * $i = $(($num * $i))"
done
echo ""
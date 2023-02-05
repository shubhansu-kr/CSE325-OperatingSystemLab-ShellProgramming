# !/bin/bash

echo "Loops in Shell Programming"

read -p "Enter num: " n 

# Iterate i from 1 to 10: Both inclusive
for i in {1..10}
do
    echo "$i"
done 

# Print table 
for i in {1..10}
do
    echo "$n * $i = " $(($n * $i))
done 
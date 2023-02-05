# !/bin/bash

read -p "Enter num1: " num1 
read -p "Enter num2: " num2
read -p "Enter num3: " num3

if [ $num1 -ge $num2 ] && [ $num1 -ge $num3 ]
then 
    echo "$num1 is the greatest"
elif [ $num2 -ge $num1 ] && [ $num2 -ge $num3 ]
then 
    echo "$num2 is the greatest"
else 
    echo "$num3 is the greatest"
fi

   
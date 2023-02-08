# 3. WAP in shell using switch case with the following options 
# Find the factorial of a number
# Find the greatest among three numbers
# Check given number is prime or not.

# !/bin/bash

echo "-----------------------------------------"
echo ""
echo "Choose Options : "
echo ""
echo "1) Find the factorial of a number"
echo "2) Find the greatest among three numbers"
echo "3) Check given number is prime or not."
echo ""

read -p "Enter Choice: " opt
echo ""

case $opt in 
1)
    # Find the factorial of num

    read -p "Enter num: " num
    fac=1
    for((i=1; i <= num; ++i))
    do
        fac=$(($fac * $i))
    done 
    echo "Factorial of $num is $fac" ;;
2)
    # Find the greatest of three num
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
    fi ;;
3)
    # Check given number is prime
    read -p "Enter a positive number : " num 

    if [ $num -le 1 ] 
    then 
        echo "Neither Prime Nor Composite"
    else 
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
            echo "$num is Prime"
        else 
            echo "$num is not Prime"
        fi 
    fi ;;
*)
    echo "Invalid Option " ;;
esac
 
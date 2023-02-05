# !/bin/bash

echo "--------- Calculator ---------"

ch=1

while [ $ch -eq 1 ]
do 
    echo ""
    echo "Choose Option: "
    echo "1) Addition"
    echo "2) Subtraction"
    echo "3) Multiplication"
    echo "4) Division"

    echo ""
    read -p "Enter Choice: " opt
    read -p "Enter num1: " num1
    read -p "Enter num2: " num2

    case $opt in 
    1) echo "$num1 + $num2 = $(($num1 + $num2))" ;;
    2) echo "$num1 - $num2 = $(($num1 - $num2))" ;;
    3) echo "$num1 * $num2 = $(($num1 * $num2))" ;;
    4) echo "$num1 / $num2 = $(($num1 / $num2))" ;;
    *) echo "Error: Enter a valid option"
    esac

    echo ""
    read -p "Enter 1 to continue: 0 to end: "
    ch=$REPLY
done

echo ""
echo "Bye"
# !/bin/bash

echo "Variable in Shell: "

num1=21 # don't use space between assignment 
num2=15 # no space 

# Add space between operand and operator
# NoSpace: Concatination of string
# Space: Arithemetic operation

num3=`expr $num1 + $num2`
num4=$(($num1 - $num2))

echo $num3 $num4
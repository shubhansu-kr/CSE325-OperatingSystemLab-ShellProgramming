# !/bin/bash

# Extention of script - .sh
touch 00_HelloWorld.sh 

# Vi is the editor 
vi 00_HelloWorld.sh  

# once in vi editor 
# press i : insert mode 
# press ctrl+c : freeze 
# press shift+: opens saving 
# In : mode press wq 

# Shell program 

# !/bin/bash : Tells the type of shell
# Add series of commands 

# ------------------------------------------------------------------------------

# 1. 
# !/bin/bash
echo "Hello World"

# ------------------------------------------------------------------------------

# 2. 
# Read in Shell 
# !/bin/bash
echo "Enter Your name"
read name
echo "Hello $name"

# To read with hint : If we are not reading in a var, it goes to REPLY var by default
# -p : Flag to prompt message
read -p "Enter you roll: "
echo $REPLY

# To limit the number of input char
# -n 8 : Limit the number of input to 8 char: All the char after 8th char is discarded.
read -n 10 -p "Enter Your Number: " number # Store input in number var.
echo $number

# To hide the input on terminal 
# -s : Hides the input on terminal console for security purpose
# Usually used while taking password inputs 

# Order of flags matters: after p, the prompt message should be there.
# We cannot use -ps "string" : Error

read -sp "Enter your Password: " pass 
# When reading with -s the control does not goes to next line

echo ""
echo "Logged In"

# ------------------------------------------------------------------------------

# 3. File Create 
read -p "Enter the dir name: " dirName
mkdir $dirName

echo "File Created Successfully"

read -p "Enter File Name: "
touch ./$dirName/$REPLY

# ------------------------------------------------------------------------------

# 4. Conditional 

# !/bin/bash

echo "Conditionals in shell programming"

read -p "Enter your Age: " age

# IF-ELSE : Be carefull with spaces, Space sensitive 
# We have to end the if block with fi
if [ $age -ge 18 ]
then 
    echo "Welcome to party"
    echo "Multiple line block"
else 
    echo "Go Home"
fi 

# Else IF Ladder : Use elif 
if [ $age -gt 18 ]
then 
    echo "You can vote"
elif [ $age -eq 18 ]
then 
    echo "You can vote next year"
else 
    echo "You cannot vote"
fi 

# ------------------------------------------------------------------------------

# 5. Logical Operator
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

# ------------------------------------------------------------------------------

# 6. Switch Case
# !/bin/bash

echo "Switch Case in shell programming : Choose options"

echo ""
echo "1: List Files"
echo "2: Date "
echo "3: Present Working Dir"
echo ""

read -p "Enter option: " opt

case $opt in 

1) ls -alt ;;
2) date ;; 
3) pwd ;;
*) echo "Enter a valid opt: "

esac

# ------------------------------------------------------------------------------

# 7. For Loops
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

# ------------------------------------------------------------------------------

# 8. For loop Dynamic Range

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


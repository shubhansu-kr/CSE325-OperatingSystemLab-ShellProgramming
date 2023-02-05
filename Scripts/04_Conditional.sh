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
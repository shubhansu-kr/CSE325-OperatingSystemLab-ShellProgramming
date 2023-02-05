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
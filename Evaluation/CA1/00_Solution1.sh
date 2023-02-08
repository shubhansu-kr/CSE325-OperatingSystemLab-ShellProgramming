# WAP in shell with following commands : 
# Make a dir of user provided name
# Create 100Dir using commands 
# Delete all the text files starting with "vijay"
# Command to copy code of this shell file into text file.

# !/bin/bash

# Create a directory
read -p "Enter the name of directory: " dirName
mkdir $dirName

# Create 100 directory with dirName.
for i in {1..100}
do
    mkdir $dirName$i
done

# Create files to avoid error.
touch vijay1.txt vijay2.txt vijay3.txt

# Delete all the text files starting with "vijay"
rm vijay*.txt

# Command to copy this shell file into text file
cat 00_Q1.sh > output.txt
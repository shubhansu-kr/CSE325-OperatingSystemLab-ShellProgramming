# Experiment 01: Introduction to Linux Commands

# eory
# Table 1: Commands
# Commands
# Description Linux Windows
# Listing file and directories ls Dir
# Long and Time Formatted Listing ls -alt Dir
# Change directory to abc cd abc cd abc
# Change to home directory cd -
# Show current working directory pwd cd/chdir
# Create a directory abc mkdir abc mkdir abc / md abc
# Create a file file.txt touch file.txt notepad file.txt
# Command is used to update the timestamp
# of a file
# touch -
# Command is used to delete files rm Del
# Command is used to concatenate files and
# print on the monitor
# cat -
# Copy files from one directory to Another cp Copy
# Move files from one directory to Another mv Move


# Exercise: 
# 1. Explore the file system of a Window system and a Linux system, and write prime
# differences.
# 2. Create a file in you Linux system, in your current user’s home directory, named as
# file1.txt. Write your name and Registration number in the file1.txt using cat
# command. Now rename the file using mv command, the new name must be
# “yourRegistratioinNo.txt”.
# 3. Create a copy of the file you have created with your registration number. Now delete
# the original file.
# 4. Create a directory with your name and move all the files (using mv command) created
# by you in currently logged in user’s home directory.
# 5. Create multiple directories using single command. (Directories name can your
# friends’ name.

# Solution: 

# 2. Create a file and add text

# Using a single > : Leads to overwriting of file but if we use double >> it leds to appending of char to the end of file
echo "12104991: Shubhansu Kumar Singh" > text1.txt
echo "This is file 2" > text2.txt 

# Using cat command we can also write 
cat > text3.txt 
# Opens a text insertor, enter the text and click ctrl+d to exit the editor mode. 

# Rename the text1.txt to yourRegistration.txt using mv 
mv text1.txt yourRegistration.txt 

# 3. Delete the original file 
rm file1.txt 

# 4. create a directory with your name and move all the files 
mkdir Shubhansu
mv *.txt Shubhansu

# 5. Create multiple directories in a single command 
mkdir dir1 dir2 dir3 


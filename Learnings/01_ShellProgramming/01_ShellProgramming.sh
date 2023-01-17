# All the command scripts are saved in /bin folder. 

# Check the version of the bash installed on system.
/bin/bash --version

# Redirecting Output
ls -al > lsOutput.txt

# Append the result at the end of the file.
ps >> psOutput.txt

# Put output and error information into seperate files. 
kill -HUP 1244 > killout.txt 2 > killerr.txt

more < killerr.txt 
# more is a filter user to create paging in large files. 

# Pipes are used to execute commands in an order and take the output
# of first command as input of second. 

ps > psout.txt
sort psout.txt > pssort.out

# Instead of using two different commands we can use pipes
ps | sort > pssort.out 

# Page the output of ps 
ps | sort | more 

# Different process names that are running excluding shell 
ps -xo comm | sort | uniq | grep -v sh | more 
# Output of ps sorted in alphabetical order. extract processes using uniq
# uses grep -v sh to remove shell from process list 
# and finally more to page the output.

# You will endup with an empty file because you  will overwrite 
# mydata.txt file before you read it. 
cat mydata.txt | sort | uniq > mydata.txt 
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
read -p "Enter the dir name: " dirName
mkdir $dirName

echo "File Created Successfully"

read -p "Enter File Name: "
touch ./$dirName/$REPLY

echo "Practice"

read -p "Enter directory name" dirName

mkdir $dirName

for i in {1..100}
do 
    touch ./$dirName/file$i.txt
done

rm vijay*.txt 
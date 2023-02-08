# 2. WAP in shell to print the result of student
# No. of student should be 5
# Output should contain Subject wise grades. 
# final grade and CGPA must be printed.

# !/bin/bash
echo "---------------Result Calculator----------------"
echo ""

sum=0
for i in {1..5}
do 
    read -p "Enter marks of sub$i: " marks$i
    sum=$(($sum + $((marks$i))))
done 

echo ""
echo "Sub : Marks : Grade"
echo ""

credit=0
grade="A"
for i in {1..5} 
do 
    if [ $((marks$i)) -gt 90 ]
    then 
        grade="O"
        credit=$(($credit + 10))
    elif [ $((marks$i)) -gt 80 ]
    then 
        grade="A+"
        credit=$(($credit + 9))
    elif [ $((marks$i)) -gt 70 ]
    then 
        grade="A"
        credit=$(($credit + 8))
    elif [ $((marks$i)) -gt 60 ]
    then 
        grade="B+"
        credit=$(($credit + 7))
    elif [ $((marks$i)) -gt 50 ]
    then 
        grade="B"
        credit=$(($credit + 6))
    else
        grade="C"
        credit=$(($credit + 5))
    fi

    echo "$i   : $((marks$i)) : $grade"   
done 

cgpa=$(($credit / 5))
credit=$cgpa

if [ $credit -gt 9 ]
then 
    grade="O"
elif [ $credit -gt 8 ]
then 
    grade="A+"
elif [ $credit -gt 7 ]
then 
    grade="A"
elif [ $credit -gt 6 ]
then 
    grade="B+"
elif [ $credit -gt 5 ]
then 
    grade="B"
else
    grade="C"
fi

echo ""
echo "Total Marks: $sum"
echo "CGPA: $cgpa "
echo "Final Grade: $grade"
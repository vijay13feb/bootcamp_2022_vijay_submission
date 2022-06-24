#! /bin/bash
printf "Enter the number: "
read digits
sum=0
for ((i=0; i<${#digits}; i++))
do
sum=$(("${digits:$i:1}"+$sum))
done
echo "Sum of the digits is: "$sum
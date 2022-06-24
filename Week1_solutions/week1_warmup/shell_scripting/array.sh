#! /bin/bash
arr=("man" "bear" "pig" "dog" "cat" "sheep")
for ((i=0; i<${#arr[*]}; i++ ))
do
echo ${arr[i]}
done
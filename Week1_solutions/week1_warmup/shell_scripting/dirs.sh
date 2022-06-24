#! /bin/bash
mkdir root
for ((i=1; i<6; i++))
do
mkdir "root/dir$i"
for ((j=1; j<5; j++))
do
yes $j | head -$j >> "root/dir$i/file$j"
done
done

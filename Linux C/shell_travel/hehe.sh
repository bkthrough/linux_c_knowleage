#!/bin/bash


value1=10
value2=10
if [ $value1 -eq $value2 ]
then
    echo "match"
else
    echo "not match"
fi

#while true
#do
#    echo 'always while'
#    sleep 0.1
#done
while true
do
    n=$((n+1))
    if [ $n -le 128 ]
    then
        echo 'n <= 128'
    else
        break
    fi
    echo $n
    #((n++))
    #n=$(echo 'n+1'|bc)
done
function fun1
{
    echo "$#,$*"
    echo "$0"
}
fun2()
{
    echo "$#,$*"
}
fun1 alskdjz zlkxc askdj
fun2 $r

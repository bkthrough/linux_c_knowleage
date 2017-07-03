#!/bin/bash

VAL="cat 123"
VAL2=asd

SUM=$(echo "$VAL+10")

:<<EOF
if [ $VAL = $VAL2 ]
then
    echo "match"
else
    echo "not match"
fi
EOF

echo $VAL
for x in $VAL
do
    echo $x
    ((n++))
done
echo "$n"
while true
do
    echo "ok"
    break
done
func()
{
    echo "hello world"
}
func

#!/bin/bash

declare -a MY_ARRAY
MY_ARRAY=($*)

echo "result:"
for num in ${MY_ARRAY[@]}
do
  printf $num" "
done
echo
FIN_FLAG=0
if [ $# -ge 1 ]; then
    for((i=1;i<$#-1;i++))
    do
      for((j=0;j<$#-1;j++))
      do
        echo "1:"${MY_ARRAY[$j]}
        echo "2:"${MY_ARRAY[$next]}
        next=$(($j +1))
        if [ ${MY_ARRAY[$j]} -gt ${MY_ARRAY[$next]} ];then
          my_temp=${MY_ARRAY[$j]}
          MY_ARRAY[$j]=${MY_ARRAY[$next]}
          MY_ARRAY[$next]=$my_temp
        fi
      done
    done
    FIN_FLAG=1
fi

echo "result:"
for num in ${MY_ARRAY[@]}
do
  printf $num" "
done

echo

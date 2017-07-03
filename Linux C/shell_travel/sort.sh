#!/bin/bash

declare -a ARRAYA
ARRAYA=($*)
func()
{
    for ((i=0;i<$#-1;++i))
    do
        for ((j=$i;j<$#;++j))
        do
            if [ ${ARRAYA[$i]} -gt ${ARRAYA[$j]} ]
            then
                tmp=${ARRAYA[$i]}
                ARRAYA[$i]=${ARRAYA[$j]}
                ARRAYA[$j]=${tmp}
            fi
        done
    done
    for ((i=0;i<$#;++i))
    do
        echo ${ARRAYA[$i]}
    done
}
func $*

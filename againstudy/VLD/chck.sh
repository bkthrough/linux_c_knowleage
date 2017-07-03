#!/bin/bash

#使用/bin/memcheck就可以直接做检测
#/bin/memcheck [.c/.cpp文件]
#不用包含vld那个头文件

#命令行结果给变量赋值的两个方法
#1.  变量=`命令行`
#2.  变量=$(命令行)
FILE=$@
MODE=`echo "$FILE" | awk -F "." '{print $2}'`
NUM=`wc -l $FILE | awk -F " " '{print $1}'`
i=1

rm -f qwertyu*
if [ $MODE == 'c' ]
then
    while true
    do
        CONTENT=$(cat $FILE | head -n $i | tail -n 1)
        #正则表达式，匹配以#include开头的行，如果没有了那么就跳出循环
        if [[ $CONTENT =~ ^"#include" ]]
        then
            echo $CONTENT >> qwertyu.c
        else
            break
        fi
        #如果达到了文件的尾部，那么就推出
        if [ $i == $NUM ]
        then
            break
        fi
        ((i++))
    done
    echo "#include <vld_c.h>" >> qwertyu.c
    while true
    do
        CONTENT=$(cat $FILE | head -n $i | tail -n 1)
        if [[ $CONTENT =~ ^"#include" ]]
        then
            ((i++))
            continue
        else
            echo "$CONTENT" >> qwertyu.c
        fi
        if [ $i == $NUM ]
        then
            break
        fi
        ((i++))
    done
    g++ qwertyu.c -o qwertyu -lvldc
    echo `./qwertyu`
    rm -f qwertyu*

elif [ $MODE == "cpp" ]
then
    while true
    do
        CONTENT=$(cat $FILE | head -n $i | tail -n 1)
        #正则表达式，匹配以#include开头的行，如果没有了那么就跳出循环
        if [[ $CONTENT =~ ^"#include" ]]
        then
            echo $CONTENT >> qwertyu.cpp
        else
            break
        fi
        #如果达到了文件的尾部，那么就推出
        if [ $i == $NUM ]
        then
            break
        fi
        ((i++))
    done
    echo "#include <vld.h>" >> qwertyu.cpp
    while true
    do
        CONTENT=$(cat $FILE | head -n $i | tail -n 1)
        if [[ $CONTENT =~ ^"#include" ]]
        then
            ((i++))
            continue
        else
            echo "$CONTENT" >> qwertyu.cpp
        fi
        if [ $i == $NUM ]
        then
            break
        fi
        ((i++))
    done
    g++ qwertyu.cpp -o qwertyu -lvldcpp
    echo `./qwertyu`
    rm -f qwertyu*
fi

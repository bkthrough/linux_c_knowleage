#!/usr/bin/awk -f
#以\t为输出分割条件，输出1,2,3列元素
BEGIN{
    OFS="\t"}
    {print $1,"\t"$2,$3}


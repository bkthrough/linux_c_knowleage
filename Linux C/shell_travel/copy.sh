#!/bin/bash
#把/usr/include所有.h文件，以/include/文件并且加入后缀
#_UNIX形式放到/mnt下。如/usr/include/video/edid.h
#在/mnt/include/video/edid.h
#找到所有.h文件名放到dir变量
DIR=$(find /usr/include -name *.h)
AINDEX=_UNIX
#从变量dir开始到结束
for FIL in $DIR
do
  #存入include/文件（如果有这个文件的话）/(不包括.h)
  DIR1=$(echo $FIL | awk -F "/" '{for(i=3;i<NF;++i) printf $i"/"}')
  #存入.h
  DIR2=$(basename $FIL)
  NEWDIR=/mnt/$DIR1
  #创建文件夹
  mkdir -p $NEWDIR
  DST=$NEWDIR$DIR2$AINDEX
  cp  $FIL $DST
done

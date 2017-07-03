#!/bin/bash

DIR=$(pwd)

echo "
[mplayer]
name=mplayer
baseurl=file://$DIR
gpgcheck=0
" >/etc/yum.repos.d/mplayer.repo

createrepo ./
yum clean all
yum install mplayer smplayer xvidcap -y

rm /etc/yum.repos.d/mplayer.repo
sleep 2
yum clean all
echo "======================"
echo "Finished ."
echo "======================"


HEAD     = ../head/
ROOTPATH = $(shell pwd)
#DST      = libmul.so
DST      = libmul.a
#ARG      = -shared -fpic
ARG      = ar -rc
OPA      = /sbin/ldconfig
SRC      = Smultip_user

ALL : $(SRC).c
	$(CC)  -c $(SRC).c  -o  $(SRC).o  -I$(HEAD)
	#$(CC) $(ARG) $(SRC) -o $(DST) -I$(HEAD)
	$(ARG) $(DST)  $(SRC).o
	#$(OPA) $(ROOTPATH)

clean :
	@rm -f *.so

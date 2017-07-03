CC		= gcc -g -Wall
CFLAGS	= -I include/ -lpthread
UTIL_SRC = util/*.c
MASTER_SRC = master/*.c
REGION_SRC = region/*.c
CLI_SRC = cli/*.c

all:startMaster startRegion yuncli

startMaster:
		$(CC) $(CFLAGS) ${UTIL_SRC} ${MASTER_SRC} -o startMaster
startRegion:
		$(CC) $(CFLAGS) ${UTIL_SRC} ${REGION_SRC} -o startRegion
yuncli:
		$(CC) $(CFLAGS) ${UTIL_SRC} ${CLI_SRC} -o yuncli

.PHONY:clean
clean:
	rm startMaster
	rm startRegion
	rm yuncli

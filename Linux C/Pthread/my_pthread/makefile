ROO_PATH = $(shell pwd)
BIN_PATH = $(ROO_PATH)/bin
SRC_PATH = $(ROO_PATH)/src
INC_PATH = $(ROO_PATH)/include
COM_PATH = $(ROO_PATH)/com
TES_PATH = $(ROO_PATH)/test_pro
ON_SUCCE = "lib create ok!"
REMOVE   = "rmove ok!"

all : create

create : load
	$(CC) -fpic -shared $(SRC_PATH)/thread_pool.c -o $(COM_PATH)/libpthread_pool.so -I$(INC_PATH)

load :
	/sbin/ldconfig $(COM)
	echo $(ON_SUCCE)
install:
	$(CC) $(SRC_PATH)/thread_pool.c $(TES_PATH)/test.c -o $(BIN_PATH)/test -pthread -I$(INC_PATH)

.PHONY:clean
clean:
	rm -f $(COM_PATH)/libpthread_pool.so $(BIN_PATH)/test
	echo $(REMOVE)



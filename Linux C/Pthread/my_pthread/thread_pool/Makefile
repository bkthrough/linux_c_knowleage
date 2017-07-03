ROOTPATH = $(shell pwd)
SRC      = $(ROOTPATH)/src
LIB      = $(ROOTPATH)/lib
HEAD     = $(ROOTPATH)/head
BIN      = $(ROOTPATH)/bin

all : collect
	cd $(SRC) && $(CC) test.c -o test -lpthread_pool -L$(LIB) -pthread -I$(HEAD)
	@mv $(SRC)/test $(BIN)
collect :
	cd $(SRC) && $(CC) -fpic -shared pthread_ctl.c -o libpthread_pool.so -I$(HEAD)
	@mv $(SRC)/libpthread_pool.so $(LIB)
	/sbin/ldconfig $(LIB)

.PHONY:clean
clean:
	@cd $(LIB) && rm -f libpthread_pool.so
	@rm -f $(BIN)/test

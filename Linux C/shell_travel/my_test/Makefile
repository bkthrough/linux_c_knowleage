
ROOTPATH = $(shell pwd)
SRC      = $(ROOTPATH)/src
BIN      = $(ROOTPATH)/bin
HEAD     = $(ROOTPATH)/head
LIB      = $(ROOTPATH)/lib
ARG      = -lncurses -lmul -L$(LIB)
COM      = $(ROOTPATH)/com
DST      = $(BIN)/multi

ALL : $(DST)

$(DST) : collect
	$(CC) $(COM)/* -o $(DST) -I$(HEAD) $(ARG)

collect :
	@cd $(SRC) && make
	@cd $(LIB) && make

clean :
	@rm -f $(BIN)/*
	@cd $(LIB) && make clean
	@cd $(SRC) && make clean

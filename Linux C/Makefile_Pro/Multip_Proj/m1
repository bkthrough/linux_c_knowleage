

ROOT  =   $(shell pwd)
SRC   =   $(ROOT)/src
BIN   =   $(ROOT)/bin
COM   =   $(ROOT)/com
HEAD  =   -I$(ROOT)/head

TGT   =   $(BIN)/mul2018
LIB   =   -lncurses
OBJ   =   $(COM)/Multip_Prj.o        \
          $(COM)/Smultip_caculate.o  \
          $(COM)/Smultip_init.o

all : $(TGT)

$(TGT) : collect
				$(CC) -o $@ $(OBJ) $(LIB)
				@echo "--------------------"
				@date
				@cd $(BIN) && ls --color=auto -l `basename $(TGT)`
				@echo "===================="

collect:
	@cd $(COM) && make

.PHONY : clean
clean  : 
				@cd $(COM) && make clean
				rm -fr $(TGT)
				@echo "--------------------"
				@date
				@echo "===================="

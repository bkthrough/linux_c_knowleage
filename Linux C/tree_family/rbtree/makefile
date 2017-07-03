#makefile
NOWPATH = $(shell pwd)
DIRC    = $(NOWPATH)/cdir
DIRH    = $(NOWPATH)/hdir
DOCO    = $()

#下层的.c文件make完生成.o文件，放到一个新建文件中，然后和.h文件
#一起生成elf文件
ALL : collect
	$(CC) $(DOCO) -o $@ -I$(DIRH)

collect:
	@cd $(DIRC) && make

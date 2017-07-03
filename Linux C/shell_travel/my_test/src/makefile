
ALL : Multip_Prj.o  Smultip_caculate.o  Smultip_init.o

%.o : %.c
	gcc -c $< -I../head
	@mv $@ ../com/

#伪目标，如果有重名的文件如当前文件夹还有一个clean文件
#如果没有下面一行，就不会执行 make clean。
.PHONY : clean
clean :
	@rm -f *.o
	@rm -f ../com/*

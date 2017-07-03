
ALL : stack.o queue.o tools.o main.o my_dlist.o tree.o
	$(CC) $+ -o main
	@mv $+ object

%.o : %.c
	$(CC) -c $+ -g

clean :
	@rm -f main
	@cd object && rm -f *.o

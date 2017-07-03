SRC=pthread_rwlock_init.cpp pthread_rwlock_destroy.cpp pthread_rwlock_rdlock.cpp pthread_rwlock_wrlock.cpp pthread_rwlock_unlock.cpp
OBJ=test.o pthread_rwlock_init.o pthread_rwlock_destroy.o pthread_rwlock_rdlock.o pthread_rwlock_wrlock.o pthread_rwlock_unlock.o
all:test
test:$(OBJ)
	g++ -o test $(OBJ) -lpthread
$(OBJ):$(SRC)

.PHONY:clean
clean:
	rm *.o  test


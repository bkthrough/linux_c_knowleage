
OBJS=convert.o convert_cpptoc.o  convert_ctocpp.o utili.o

all:convert

convert: ${OBJS}
	g++ -o convert ${OBJS} -g
convert.o: utili.h convert.cpp
	g++ -o convert.o -c convert.cpp -g
utili.o:utili.h utili.cpp
	g++ -o utili.o -c utili.cpp -g
convert_cpptoc.o:utili.h convert_cpptoc.cpp
	g++ -o convert_cpptoc.o -c convert_cpptoc.cpp -g
convert_ctocpp.o:utili.h convert_ctocpp.cpp
	g++ -o convert_ctocpp.o -c convert_ctocpp.cpp -g

install:
	cp convert /bin/

.PHONY:clean
clean:
	rm ${OBJS} convert

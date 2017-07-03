all:cli ser

cli:cli.cpp
	g++ cli.cpp -o cli -g
ser:ser.cpp
	g++ ser.cpp -o ser -g

.PHONY:clean

clean:
	rm -f ser cli

process:pool/pser cli
	g++ cli.cpp -o cli -g -pthread
	@cd process && g++ ser.cpp -o ser -g -pthread
pool:pool/ser cli
	g++ cli.cpp -o cli -g -pthread
	@cd pool && g++ ser.cpp -o ser -g -pthread


.PHONY:clean

clean:
	rm -f ser cli

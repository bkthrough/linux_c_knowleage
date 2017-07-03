default:main1
main1:cpptransfertoc.cpp ctransfertocpp.cpp
	g++ cpptransfertoc.cpp ctransfertocpp.cpp main.cpp -o main -g -Ddefault
order:main
main:cpptransfertoc.cpp ctransfertocpp.cpp
	g++ cpptransfertoc.cpp ctransfertocpp.cpp main.cpp -o main -g -Dorder

.PHONY:clean

clean:
	rm -f main.o main

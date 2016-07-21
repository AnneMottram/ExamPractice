multitap: main.o multitap.o
	g++ -g -Wall main.o multitap.o -o multitap

main.o: main.cpp multitap.h
	g++ -g -Wall -c main.cpp 

multitap.o: multitap.cpp multitap.h
	g++ -g -Wall -c multitap.cpp

.PHONY:clean
clean:
	rm -f multitap *.o
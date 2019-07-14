all:
	g++ -Wall -std=c++11 -o senceiver -pthread senceiver.cpp sock.c
.PHONY : clean
clean :
	rm -f *.o *.d *~ senceiver
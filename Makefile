Project2 : Project2.o
	g++ -o Project2 Project2.o

Project2.o :
	g++ -c Project2.cpp -o Project2.o

clean :
	rm -rf *.o Project2
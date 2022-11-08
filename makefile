thread: mainProgram.cpp
	gcc -std=c99 -c -o Video.c.o Video.c -w -lpthread
	gcc -std=c99 -c -o Video.h.o Video.h -w -lpthread
	g++ -std=c++0x -c -o mainProgram.cpp.o mainProgram.cpp -w -lpthread
	g++ -o executable mainProgram.cpp.o Video.c.o Video.h.o

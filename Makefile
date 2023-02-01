exe: main.o
	g++ -g -Wall main.o -o exe
main.o: main.cpp Graph.h
	g++ -g -Wall -c main.cpp
clean:
	rm exe prog *.o myout*
test: main.o
	g++ -std=c++11 main.o -o prog && ./prog <input1.txt >myout1.txt && ./prog <input2.txt >myout2.txt && ./prog <input3.txt >myout3.txt && ./prog <input4.txt >myout4.txt

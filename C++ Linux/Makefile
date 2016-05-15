all:
	g++ -std=c++11 -Wall -fPIC -O2 -c Kazelib.cpp Kazelib.h  `pkg-config --cflags --libs mono-2`
	g++ -std=c++11 -shared -o Kazelib.so Kazelib.o   `pkg-config --cflags --libs mono-2`
	g++ -std=c++11 main.cpp -ldl
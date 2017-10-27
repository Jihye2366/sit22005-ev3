all: ev3dev.a sound-test.o h_crane.o
	arm-linux-gnueabi-g++-4.7 -L. -o sound-test sound-test.o h_crane.o -lev3dev

ev3dev.a: ev3dev.cpp 
	arm-linux-gnueabi-g++-4.7 -c ev3dev.cpp -o ev3dev.o -std=c++11 -D_GLIBCXX_USE_NANOSLEEP
	ar -r libev3dev.a ev3dev.o

sound-test.o: sound-test.cpp
		arm-linux-gnueabi-g++-4.7 -c sound-test.cpp -o sound-test.o -std=c++11 -D_GLIBCXX_USE_NANOSLEEP
		
h_crane.o: h_crane.cpp
		arm-linux-gnueabi-g++-4.7 -c h_crane.cpp -o h_crane.o -std=c++11 -D_GLIBCXX_USE_NANOSLEEP
		
clean:
	rm *.a
	rm *.o
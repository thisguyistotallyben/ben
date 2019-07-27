all: driver

driver: ben.o driver.o benvisual.o
	g++ -o driver ben.o driver.o benvisual.o

ben.o: ben.h ben.cpp
	g++ -c ben.cpp

benvisual.o: ben.h benvisual.cpp
	g++ -c benvisual.cpp

driver.o: driver.cpp ben.h
	g++ -c driver.cpp

all: driver

driver: ben.o benview.o driver.o
	g++ -o driver ben.o benview.o driver.o -lncurses -lpanel -pthread

ben.o: ben.h benview.h ben.cpp
	g++ -c ben.cpp

benview.o: benview.h benview.cpp
	g++ -c benview.cpp

driver.o: driver.cpp ben.h
	g++ -c driver.cpp

clean:
	rm *.o driver

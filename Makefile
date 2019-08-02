all: driver

driver: ben.o ben_widget.o ben_view.o ben_server.o driver.o
	g++ -o driver ben.o ben_widget.o ben_view.o ben_server.o driver.o -lncurses -lpanel -pthread

ben.o: ben_common.h ben.h ben_view.h ben_server.h ben.cpp
	g++ -c ben.cpp

ben_widget.o: ben_common.h ben_widget.cpp
	g++ -c ben_widget.cpp

ben_view.o: ben_common.h ben_view.h ben_view.cpp
	g++ -c ben_view.cpp

ben_server.o: ben_common.h ben_server.h ben_view.h ben_server.cpp
	g++ -c ben_server.cpp

driver.o: driver.cpp ben.h
	g++ -c driver.cpp

clean:
	rm *.o driver

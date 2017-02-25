CXXFLAGS = -std=gnu++14 -Wall
LDLIBS = -lstdc++

.PHONY: all clean test

all: webots-client

clean:
	-rm webots-client *.o

test_server:
	node example-server.js

node_modules:
	npm install

webots-client: webots-client.o walk-client.o
easywsclient: easywsclient.o
webots-client.o: webots-client.cpp webots-client.h
walk-client.o: walk-client.cpp walk-client.h
easywsclient.o: easywsclient.cpp easywsclient.hpp

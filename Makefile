CXXFLAGS = -std=gnu++0x -Wall
LDLIBS = -lstdc++
.PHONY: all clean test
all: webots-client
clean: \
-rm webots-client *.o \
cd test; $(MAKE) clean
test: \
cd test; $(MAKE) test
test server: \
node example-server.js
node_modules: \
npm install
webots-client: webots.client.o //do i need to include easywsclient files
webots-client.o: webots-client.cpp webots-client.h

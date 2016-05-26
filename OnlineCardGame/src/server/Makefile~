#Kamil Zielinski
#make dla server

CC=gcc
CXX=g++
CFLAGS=-c
CXXFLAGS=-c
LDFLAGS=
CSOURCES=server.cpp connection.cpp playerhandler.cpp spechandler.cpp game.cpp karta.cpp
SOURCES=$(CSOURCES)
OBJECTS=$(CSOURCES:.c=.o) 
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS)-pthread -o $@ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o  $@

clean:
	rm *.o

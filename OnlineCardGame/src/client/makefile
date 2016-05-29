# Autor: Kamil Zieliński
# Makefile dla clienta

CC=gcc
CXXFLAGS=-c
LDFLAGS=
CSOURCES=client.cpp connectionn.cpp game.cpp chat.cpp chatKomentowanie.cpp
SOURCES=$(CSOURCES) 
OBJECTS=$(CSOURCES:.c=.o)
EXECUTABLE=client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -pthread -std=c++11 -o $@ $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o


# Autor: Kamil Zieliński
# Make dla clienta

CC=gcc
CXXFLAGS=-c
LDFLAGS=
CSOURCES=client.c connectionn.c 
SOURCES=$(CSOURCES) 
OBJECTS=$(CSOURCES:.c=.o)
EXECUTABLE=client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.c.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o


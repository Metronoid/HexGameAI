EXECUTABLE=hex

CC=g++
CFLAGS=-c -Wall -Ofast -std=c++11 -g
LDFLAGS=-g

DEPS=$(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)



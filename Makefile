CC=g++
CFLAGS=-c --std=c++1y -Wall -Wextra
LDFLAGS=-lboost_python3 -lboost_program_options
SOURCES=main.cpp Generator.cpp Base.cpp Second.cpp First.cpp Diagram.cpp TimeCounter.cpp
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES=$(shell pkg-config --cflags --libs python-3.5) 
EXECUTABLE=py

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) ; $(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(INCLUDES)

.cpp.o: ; $(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(INCLUDES)

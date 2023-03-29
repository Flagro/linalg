CC=/opt/homebrew/bin/g++-12
CFLAGS=-c -Wall -Wextra -std=c++17 -fopenmp
SOURCES=linalg_containers.cpp linalg_operations.cpp linalg_algorithms.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

RM=rm -f

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -fopenmp

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS)

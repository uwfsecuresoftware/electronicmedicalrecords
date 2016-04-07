CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp term.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=emr

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm *.o
	rm *.exe
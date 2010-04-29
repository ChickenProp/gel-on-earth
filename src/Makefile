CC = g++
CFLAGS = -Wno-write-strings
LDFLAGS = -lGL -lsfml-system -lsfml-window
exec = ../gel-on-earth
headers = $(wildcard *.h)
sources = $(wildcard *.cpp)
objects = $(sources:.cpp=.o)

all: $(exec)

$(exec): $(objects)
	$(CC) -g -o $(exec) $(objects) $(CFLAGS) $(LDFLAGS)

%.o: %.cpp $(headers)
	$(CC) -g $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *~ $(objects) $(exec)

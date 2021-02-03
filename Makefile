pool: main.cc
	$(CC) -std=c++98 -o pool main.cc -lstdc++

.PHONY: all clean

clean:
	rm -f *.o
	rm -f pool

all: pool

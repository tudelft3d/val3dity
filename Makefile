# Options
CC=c++
IPATH=/usr/local/include/
LPATH=/usr/local/lib/
CFLAGS=-frounding-math -fno-strict-aliasing -O3 -DNDEBUG -I$(IPATH) -L$(LPATH)
LIBS=-lCGAL_Core -lCGAL -lmpfr -lgmp -lboost_thread-mt
LDFLAGS=-frounding-math -fno-strict-aliasing -O3 -DNDEBUG -Wl -lGL -L$(LPATH) $(LIBS)

all: main

input.o: input.cpp
	$(CC) $(CFLAGS) -c $^

validate.o: validate.cpp
	$(CC) $(CFLAGS) -c $^

validate_shell.o: validate_shell.cpp
	$(CC) $(CFLAGS) -c $^

validate_solid.o: validate_solid.cpp
	$(CC) $(CFLAGS) -c $^

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^

main:  input.o validate.o validate_shell.o validate_solid.o main.o
	$(CC) $(LDFLAGS) $^ -o val3dity 

clean:
	rm -rf *.o main

cc = g++
CFLAGS = -Wall -Wextra -g -o
SRC = main.cpp
EXE = tema4

build:
	$(cc) $(CFLAGS) $(EXE) $(SRC)
clean:
	rm $(EXE)
run:
	./tema4

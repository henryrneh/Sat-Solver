CC = g++
FLAGS = --std=c++17 -O3 -flto -Wall -Wextra -pedantic -Wnull-dereference -Wfloat-equal -Wundef -Wcast-qual -Wcast-align -Wodr -Wold-style-cast -Wmissing-include-dirs -Wswitch-enum -Wswitch-bool -Wmissing-declarations -Wimplicit-fallthrough=5 -Wdouble-promotion -Wstrict-overflow=5 -Wformat=2 -Wformat-overflow=2
EXEC = sat

all:
	@echo "Building ..."
	$(CC) $(FLAGS) sat.cpp -o $(EXEC)
	@echo "Done."

clean:
	@echo "Cleaning up..."
	rm $(EXEC)
	@echo "Done."


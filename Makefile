CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17
CFLAGS = -std=c++17
INCDIRS = 
LIBDIRS = 
SRC = taxi_assignment_instance.cpp taxi_assignment_solution.cpp checker.cpp greedy_solver.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = taxi_batching

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
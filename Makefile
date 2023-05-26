CC = g++
CFLAGS = -std=c++17
INCDIRS =<path_to_ortools>/include/
LIBDIRS = <path_to_ortools>/lib/
SRC = taxi_assignment_instance.cpp taxi_assignment_solution.cpp checker.cpp greedy_solver.cpp taxi_assignment_batching_solver.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = taxi_batching

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -L$(LIBDIRS) -lortools -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCDIRS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
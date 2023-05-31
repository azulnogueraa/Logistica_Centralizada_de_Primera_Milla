CC = g++
CFLAGS = -std=c++17

INCDIRS = /Users/achula/achula/td5/tp1/or-tools_arm64_macOS-13.2.1_cpp_v9.6.2534/include/
LIBDIRS = /Users/achula/achula/td5/tp1/or-tools_arm64_macOS-13.2.1_cpp_v9.6.2534/lib/

# INCDIRS = /Users/rochigc/Documents/1_2023/TDV/or-tools_arm64_macOS-13.2.1_cpp_v9.6.2534/include/
# LIBDIRS = /Users/rochigc/Documents/1_2023/TDV/or-tools_arm64_macOS-13.2.1_cpp_v9.6.2534/lib/

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

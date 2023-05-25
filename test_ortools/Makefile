CC = g++
CFLAGS = -std=c++17
INCDIRS = <path_to_ortools>/include/
LIBDIRS = <path_to_ortools>/lib/
SRC = test_flow.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = test_flow

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -L$(LIBDIRS) -lortools -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCDIRS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
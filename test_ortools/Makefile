CC = g++
CFLAGS = -std=c++17
INCDIRS = /Users/achula/achula/td5/tp1/or-tools_arm64_macOS-13.2.1_cpp_v9.6.2534/include/
LIBDIRS = /Users/achula/achula/td5/tp1/or-tools_arm64_macOS-13.2.1_cpp_v9.6.2534/lib/
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
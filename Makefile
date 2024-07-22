# C++ compiler (adjust if necessary)
CC = g++

# C++ standard and warning flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Linker flags (optional, add libraries here)
LDFLAGS =  # Space added here

# Object files (one for each source file)
OBJ = main.o

# Executable name
EXEC = cdir

# Main target (build the executable)
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC) $(OBJ)

# Build object files from source files
main.o: main.cpp utils.h
	$(CC) $(CXXFLAGS) -c main.cpp

# Clean up (remove object and executable files)
clean:
	rm -f $(OBJ) $(EXEC)

# Run the executable (optional)
run:
	./$(EXEC)

# Phony targets
.PHONY: all clean run


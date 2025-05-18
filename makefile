# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17

# Target executable
TARGET = demo

# Source files
SRCS = Demo.cpp

all: $(TARGET)

# Build target
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean target
clean:
	rm -f $(TARGET)
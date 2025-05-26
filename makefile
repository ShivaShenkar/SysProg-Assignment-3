# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Target executable
TARGET = demo

# Source files
SRCS = Demo.cpp Baron.cpp Game.cpp General.cpp Governor.cpp Judge.cpp Merchant.cpp Player.cpp Spy.cpp

all: $(TARGET)

# Build target
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean target
clean:
	rm -f $(TARGET)
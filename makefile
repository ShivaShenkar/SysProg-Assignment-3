# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17

# Target executable
TARGETDEMO = bin/demo.out
TARGET = bin/main.out
TARGETTEST = bin/test.out

# Source files
SRCS = src/*.cpp
DEMOSRCS = $(SRCS) demo/Demo.cpp
TESTSRCS=

test: $(TARGETTEST)
$(TARGETTEST): $(TESTSRCS)
	$(CXX) $(CXXFLAGS) -g -o $@ $^

demo:$(TARGETDEMO)

$(TARGETDEMO): $(DEMOSRCS)
	$(CXX) $(CXXFLAGS) -g -o $@ $^

all: $(TARGET)

$(TARGET): $(SRCS) 
	$(CXX) $(CXXFLAGS) -g -o $@ $^

clean:
	rm -rf bin/*

.PHONY: all clean demo
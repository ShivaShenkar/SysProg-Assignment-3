# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGETDEMO = bin/demo.out
TARGETMAIN = bin/main.out
TARGETTEST = bin/test.out

# Source files
SRCS = src/*.cpp
SRCGUI = src/gui/*.cpp
DEMOSRCS = $(SRCS) demo/Demo.cpp
# TESTSRC=

# test: $(TARGETTEST)
# $(TARGETTEST): $(TESTSRCS)
# 	$(CXX) $(CXXFLAGS) -g -o $@ $^

demo:$(TARGETDEMO)

$(TARGETDEMO): $(DEMOSRCS)
	$(CXX) $(CXXFLAGS) -g -o $@ $^

main: $(TARGETMAIN)

$(TARGETMAIN): $(SRCS) $(SRCGUI) main.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -g -o $@ $^

clean:
	rm -rf bin/*

.PHONY: all clean demo main
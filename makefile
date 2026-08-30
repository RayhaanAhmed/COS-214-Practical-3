CXX := g++
CXXFLAGS := -std=c++11 -Wall -g -I.

SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
TARGET := eventflow

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)

check-leaks: $(TARGET)
ifeq ($(UNAME_S),Darwin)
ifeq ($(UNAME_M),arm64)
	@echo "Apple Silicon Mac detected: valgrind isn't supported, using 'leaks' instead."
	leaks --atExit -- ./$(TARGET)
else
	@command -v valgrind >/dev/null 2>&1 && \
		valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) || \
		(echo "valgrind not found, falling back to 'leaks'"; leaks --atExit -- ./$(TARGET))
endif
else
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)
endif

# Explicit targets in case you want to force a specific tool:
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

leaks: $(TARGET)
	leaks --atExit -- ./$(TARGET)

.PHONY: check-leaks valgrind leaks
CXX := g++
CXXFLAGS := -std=c++11 -Wall -g -Iinclude

SRC_DIR := src
BUILD_DIR := build
TARGET := eventflow

SOURCES := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/leaves/*.cpp $(SRC_DIR)/observer/*.cpp main.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
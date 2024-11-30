# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./include

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/healthcare_system

# Default target
all: $(TARGET)

# Rule to build the final executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)  # Create bin directory if not exists
	$(CXX) $(OBJECTS) -o $(TARGET)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)  # Create obj directory if not exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Rule for running the binary
run: $(TARGET)
	$(TARGET)

# To avoid rebuilding if nothing changes
.PHONY: all clean run


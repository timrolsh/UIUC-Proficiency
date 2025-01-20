#!/bin/bash

# Base directory
BASE_DIR="/mnt/c/Users/jacob/projects/helloworld/All_Data_Structs"

# List of new data structures to set up
NEW_STRUCTS=("BTree" "PriorityQueue" "Trie" "DisjointSet" "SkipList" "BloomFilter")

# Boilerplate Makefile content
MAKEFILE_CONTENT='CXX = g++
CXX_FLAGS = -std=c++20 -Wall -Wextra -O0 -gdwarf-4 \
            -fsanitize=address,undefined \
            -fno-omit-frame-pointer -fno-optimize-sibling-calls \
            -fsanitize-address-use-after-scope

SRCS = ./driver.cc
INCLUDES = ./HEADER_NAME.hpp
EXEC_PATH = ./bin/HEADER_NAME

.DEFAULT_GOAL := exec

exec: $(EXEC_PATH)

$(EXEC_PATH): $(SRCS) $(INCLUDES) | bin/
	$(CXX) $(CXX_FLAGS) $(SRCS) -o $@

bin/:
	mkdir -p bin

.PHONY: exec clean

clean:
	rm -rf bin/*'

# Create directories and files for each new structure
for STRUCT in "${NEW_STRUCTS[@]}"; do
    echo "Setting up $STRUCT..."

    # Create main directory
    STRUCT_DIR="$BASE_DIR/$STRUCT"
    mkdir -p "$STRUCT_DIR/bin"

    # Create header file with include guards
    HEADER_FILE="$STRUCT_DIR/$STRUCT.hpp"
    HEADER_GUARD=$(echo "$STRUCT" | tr '[:lower:]' '[:upper:]')_HPP
    echo "#ifndef $HEADER_GUARD
#define $HEADER_GUARD

// Add your $STRUCT implementation here

#endif // $HEADER_GUARD" > "$HEADER_FILE"

    # Create a backup of the header file
    cp "$HEADER_FILE" "$HEADER_FILE.bak"

    # Create a blank test driver file
    DRIVER_FILE="$STRUCT_DIR/driver.cc"
    echo "// Test driver for $STRUCT

#include \"$STRUCT.hpp\"

int main() {
    // Add your test code here
    return 0;
}" > "$DRIVER_FILE"

    # Create Makefile and replace placeholder HEADER_NAME with structure name
    MAKEFILE_FILE="$STRUCT_DIR/Makefile"
    echo "${MAKEFILE_CONTENT//HEADER_NAME/$STRUCT}" > "$MAKEFILE_FILE"

    echo "$STRUCT setup complete."
done

echo "All structures have been set up!"
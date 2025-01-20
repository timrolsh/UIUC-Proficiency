CXX = g++
CXX_FLAGS = -std=c++20 -Wall -Wextra -O0 -gdwarf-4 \
            -fsanitize=address,undefined \
            -fno-omit-frame-pointer -fno-optimize-sibling-calls \
            -fsanitize-address-use-after-scope

SRCS = ./driver.cc
INCLUDES = ./Queue.hpp
EXEC_PATH = ./bin/Queue

.DEFAULT_GOAL := exec

exec: $(EXEC_PATH)

$(EXEC_PATH): $(SRCS) $(INCLUDES) | bin/
	$(CXX) $(CXX_FLAGS) $(SRCS) -o $@

bin/:
	mkdir -p bin

.PHONY: exec clean

clean:
	rm -rf bin/*

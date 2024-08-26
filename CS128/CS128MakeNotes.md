# Make/Makefile Notes for CS 128

## Reflection

You were not required to use make or to build anything with make on the proficiency exam. All the grader did was pull a few files from your workspace and grade them on its own. You are told which files will be pulled and those are the files you want to do your work in and make changes to. You can use make but I just compiled with clang++ command in the terminal manually adding all arguments and that was good enough for the exam.

## General Notes

* Build tool meant for C/C++ programs based on rules defined by Makefile and
* Makefiles need to be indented with tabs and not spaces
* Make works in a graph structure, directional graph that cannot be cyclic otherwise you have circular imports
* Idea is to initiate a make build and it will only rebuild the things that need to be rebuilt and those that depend on them, not anything else
* You do `make [target_name]` to run a target including phony targets
* An additional argument would run the name of the phony target for that argument
**Variables**: Used in make the same way they are used in bash, used as `$(CXX)` and defined like this:

```make
INCLDES=-I includes/
CXX=clang++
CXXFLAGS=-std=c++20 $(INCLUDES)
```

**Rule/Goal**: Each entry which defines process/file type and what to do with it
**Structure of Make Rules**

```make
output_file: dependency1 dependency2 etc.
 command args to run to execute rule
bin/main.out: src/main.cc
 $(CXX) $(CXXFLAGS) $^ -o $@
```

**Default Rule**: Rule make will run by default when you call `make` command in a file with a Makefile with no additional arguments, defined by: `.DEFAULT_GOAL :=`
**Phony**: type of target that doesn't have output file, useful for doing things like just running a compiled program with arguments, or building and running unit tests, or removing generated or cached files, you use `.PHONY : [test clean etc.]`

```make
build: bin/main.out
 bin/main.out

.PHONY : build
.DEFAULT_GOAL := build
```

## Special Automatic Variables

`$@`: Name of rule's output, where the output file is going to
`$<`: First dependency you put after the rules outputs
`$^`: All dependencies
`$(@D)`: Directory of the output

## Pattern Matching

* Useful tool for file management, common example is making sure you make headers for all the new cpp files that you make, example:

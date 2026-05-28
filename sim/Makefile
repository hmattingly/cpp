# use .PHONY to indicate this target is always a command, never a file
.PHONY: clean run build

# macros
#MACROS = VARIO MATLOOP FUNCSREFS ENUMSTRUCTS CLASSES

# compiler
CXX = clang++

# compiler flags
CXXFLAGS = -std=c++23 -c -pedantic-errors 

# preprocessor directives
CPPFLAGS = $(MACROS:%=-D%) -Iinclude

# executable name
TARGET = bin/program

# source files
SRC = $(wildcard src/*.cpp)

# object files generated from source file names
OBJ = $(SRC:src/%.cpp=obj/%.o)

# link objects together
$(TARGET): $(OBJ)
	@$(CXX) $^ -o $(TARGET)

# compile objects
obj/%.o: src/%.cpp
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

# build program
build: $(TARGET)

# execute program
run:
	@$(TARGET)

# removes all object and executable files
clean:
	@rm -f obj/*.o $(TARGET)



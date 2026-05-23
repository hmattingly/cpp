# make files consist of a set of rules with the following format:
  # targets: prerequisites
  #		command
  #		command
  #		command

# targets are file names
  # separated by spaces
  # typically one per rule
# commands are a series of steps used to make the target
  # must start with tab
# prerequisites are also file names
  # separated by spaces

# make performs the following steps:
  # 1) does the target have prerequisites?
    # if no, does the target file exist?
      # if no, execute commands
      # if yes, do nothing (prints "<target name> is up to date")
    # if yes, for each prerequisite... does the prerequisite have a defined target (rule)?
        # if yes, call the prerequisite target (rule), go to step 1
        # if no, does the prerequisite file exist?
          # if no, error (prints "no rule to make target <target name>")
          # if yes, prerequisite satisfied
    # after all prerequisites have been satisfied, is any prerequisite file newer than the target file? 
      # if no, do nothing (prints "<target name> is up to date")
      # if yes, execute commands

# by default Make will check for files in the same directory as the Makefile

# execute a Makefile by running the make <target name> command
  # simply running make will execute the first target in the Makefile


# EXAMPLE
# program: program.o
#	clang++ program.o -o program  <-- runs 2nd, links
#
# program.o: program.cpp
#	clang++ -c program.cpp -o program.o  <-- runs 1st, compiles

# when there are multiple targets for a rule, the commands will be run for each target
# EXAMPLE
# program1.o program2.o: 
#	clang++ program.cpp -o $@  <-- $@ contains the target name

# * can be used as a wildcard for targets or prerequisites, but not in variable definitions
  # the wildcard function allows use in variable definitions
  # if using in a prerequisite and no matches, it defaults to nothing
# EXAMPLE
# example = $(wildcard *.cpp)
# program: $(wildcard *.o)   <-- no prerequisite if *.o returns no matches
# 	clang++ program.o -o program

# % is also a wildcard but is confusing. Can be used in the following ways:
  # matching one or more characters in a string
  # replacing the match 
# EXAMPLE
# $(SRC:src/%.cpp=obj/%.o)
  # for every word in SRC, if it matches src/%.cpp, replace it with obj/%.o

# Variables
  # variables can only be strings
  # variables can be defined in any order

# automatic variables:
  # $@ outputs target
  # $? outputs all prerequisites newer than the target
  # $^ outputs all prerequisites
  # $< outputs the first prerequisite

# implicit, commonly used variables:
  # CXX used to define the C++ compiler, defaults to clang++ for mac (or c++)
  # CXXFLAGS used to define C++ compiler arguments, defaults to empty
  # CPPFLAGS used to define preprocessor macros
  # LDFLAGS used to define linker arguments, defaults to empty


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



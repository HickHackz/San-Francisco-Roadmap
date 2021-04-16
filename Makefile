# Executable names:
EXE = project  //rename to whatever we come up with
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o

# Use the makefile template:
include tests/make/project.mk

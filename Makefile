# Executable names:
EXE = project
TEST = tests

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o graph.o dijkstra.o

# Use the makefile template:
include cs225/make/project.mk

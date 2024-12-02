# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic

# Source files
graph_SRC = graph_functions.c main.c

# Header files
HEADER = graph.h

# Object files
graph_OBJS = $(graph_SRC:.c=.o)

# Executable name
graph_TARGET = a4

# Build target
all: $(graph_TARGET)

# Link object files to create executable
$(graph_TARGET): $(graph_OBJS)
	$(CC) $(CFLAGS) -o $@ $(graph_OBJS)

# Compile source files into object files
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(graph_TARGET) *.o
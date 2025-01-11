

# Compiler and flags
CC = gcc
CFLAGS = -O0 -m64 -I ./src/include -L ./src/lib

# Output file
OUTPUT = main

# Find all .c files dynamically
SOURCES = $(wildcard *.c)
# Generate corresponding .o files
OBJECTS = $(SOURCES:.c=.o)

# Libraries
LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Default target
all: $(OUTPUT)

# Link the object files to create the executable
$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	del /q $(OBJECTS) $(OUTPUT)

rebuild: all clean
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Source files
SRCS = main.c game.c helper.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = traffic

# Targets
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) -c $< -o $@

# Clean rule
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean

//

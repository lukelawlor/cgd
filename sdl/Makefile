# The C compiler we are using
CC=gcc

# C flags
# -Wall and -Wextra print all error messages
CFLAGS=-Wall -Wextra -w

# Linker flags
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer

# Source, object, and binary files
# Binary file extension
BINS_EXT=.exe
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
BINS=$(SRCS:.c=$(BINS_EXT))

all: $(BINS)

# Link object files
%$(BINS_EXT): %.o
	$(CC) $< -o $@ $(LDFLAGS)

# Compile source files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

.DELETE_ON_ERROR:
.PHONY: clean
clean:
	rm $(BINS)
	rm $(OBJS)

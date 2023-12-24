CC := gcc
DEPFLAGS := -MMD -MP

BIN := inline

all: $(BIN)

SRCS := main.c sum.c
OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

main.o: main.c sum.h
sum.o: sum.c sum.h
sum.h:

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $(DEPFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(OBJS) $(DEPS) $(BIN)

.DELETE_ON_ERROR:

-include $(DEPS)

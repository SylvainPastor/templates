EXEC = template
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Werror
LDFLAGS	=

all: $(OBJS)
	@$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o $(EXEC)

TARGETS := localhost wp85

.PHONY: all $(TARGETS)
all: $(TARGETS)

EXEC = external
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGETS): $(EXEC)
	mkapp -t $@ $(EXEC).adef

clean:
	rm -rf *.o $(EXEC) _build_* *.*.update

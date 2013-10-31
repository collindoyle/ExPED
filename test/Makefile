#GNU Makefile

target := mytest

INCLUDES :=

CFLAGS := 

LDFLAGS := 

default: all
srcs := $(wildcard *.c)
objs := $(srcs:.c=.o)

all:	$(target)

$(target): $(objs)
	$(CC) -o $(target) $(objs)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm $(target)
	rm *.o

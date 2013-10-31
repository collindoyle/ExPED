#GNU Makefile

target := test

INCLUDES :=

CFLAGS := 

default: all


all:	$(target)

$(target): *.o
	$(CC) -o $(target) $(wildcard, *.o)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm $(target)
	rm *.o

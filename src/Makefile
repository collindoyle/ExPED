#GNU Makefile

build ?= debug

target := libped.a

PROJECT_ROOT := ..

SRC_FILES := $(wildcard *.c)

OBJ_FILES := $(patsubst %.c, %.o, $(SRC_FILES))

THIRD_PARTY_ROOT := ../$(PROJECT_ROOT)

THIRD_PARTY_ROOT := $(THIRD_PARTY_ROOT)/thirdparty

MUPDF_ROOT := $(THIRD_PARTY_ROOT)/mupdf


INCLUDES := -I $(MUPDF_ROOT)/include

LIBS :=

default: all 


all : $(target)
	mkdir -p $(PROJECT_ROOT)build/
	mkdir -p $(PROJECT_ROOT)build/$(build)

$(target): $(OBJ_FILES)
	ar rvs $(target) $(OBJ_FILES) $(LIBS)

.c.o: 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

clean :
	rm ./$(target)
	rm $(wildcard *.o);

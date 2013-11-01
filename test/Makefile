#GNU Makefile

build ?= debug

target := mytest

SRC_ROOT := ../src

PROJECT_ROOT := ..

THIRD_PARTY_ROOT := ../$(PROJECT_ROOT)/thirdparty

MUPDF_ROOT := $(THIRD_PARTY_ROOT)/mupdf

MUPDF_LIB_PATH := $(MUPDF_ROOT)/build/$(build)

MUPDF_INCLUDE_PATH := $(MUPDF_ROOT)/include

MUPDF_LIBS := -ljpeg -lopenjpeg -ljbig2dec -lz -lfreetype -lmupdf 

PED_LIB_PATH := $(SRC_ROOT)

PED_LIBS := -lped

INCLUDES := -I$(SRC_ROOT) -I$(MUPDF_INCLUDE_PATH)

CFLAGS :=  -Wall $(INCLUDES) 

LDFLAGS := -L$(MUPDF_LIB_PATH) $(MUPDF_LIBS) -L$(PED_LIB_PATH) $(PED_LIBS) 

default: all
srcs := $(wildcard *.c)
objs := $(srcs:.c=.o)

all:	$(target)

$(target): $(objs)
	$(CC) -o $(target) $(objs) $(LDFLAGS)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm $(target)
	rm *.o

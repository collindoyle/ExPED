#GNU Makefile

build ?= debug

THIRD_PARTY_ROOT := ../thirdparty

MUPDF_ROOT := $(THIRD_PARTY_ROOT)/mupdf

LIBXML2_ROOT := $(THIRD_PARTY_ROOT)/libxml2

SVM_ROOT := $(THIRD_PARTY_ROOT)/svm_multiclass

SVM_OBJ := $(wildcard $(SVM_ROOT)/*.o)

SVM_INCLUDE_PATH := $(SVM_ROOT)

MUPDF_LIB_PATH := $(MUPDF_ROOT)/build/$(build)

MUPDF_INCLUDE_PATH := $(MUPDF_ROOT)/include

LIBXML2_LIB_PATH := $(LIBXML2_ROOT)/.libs

LIBXML2_INCLUDE_PATH := $(LIBXML2_ROOT)/include



default: all

all: 
	mkdir -p build
	mkdir -p build/$(build)

	cd src; make;
	cd test; make;

clean:	
	rm -f build/*.a build/*.o

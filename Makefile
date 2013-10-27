#GNU Makefile

build ?= debug

all:
	mkdir -p build
	mkdir -p build/$(build)
	mkdir -p build/$(build)/mupdf
	cd mupdf; make third libs;
	cp mupdf/build/$(build)/*.a build/$(build)/mupdf/
	cd src; make;


clean:
	rm -f build/$(build)/*


default : all


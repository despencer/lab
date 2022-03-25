PREFIX ?= /usr/local
PROJECT = libopencm3

LIST := a b c d x y z
TEXT := a b x y

FA1 = $(foreach var, $(LIST), $(TEXT))

all:
	@echo use sudo make install or sudo make uninstall

install:
	@install -d $(PREFIX)/lib/$(PROJECT)
	@install -m 644 lib/* $(PREFIX)/lib/$(PROJECT)

uninstall:
	@rm -f $(PREFIX)/lib/$(PROJECT)/*
	@rmdir $(PREFIX)/lib/$(PROJECT)

list:
	@echo $(FA1)
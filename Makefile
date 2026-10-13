include ../shared.mk

SOURCES:=$(shell find . -name '*.c')
CFLAGS+=-Werror

include ../end.mk


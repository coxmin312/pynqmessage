include ../shared.mk

SOURCES:=$(wildcard *.c) $(wildcard Send/*.c) $(wildcard Receive/*.c) $(wildcard Pseudo/*.c) $(wildcard Init/*.c)
CFLAGS+=-Werror

include ../end.mk


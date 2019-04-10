CC = gcc

UNAME = $(shell uname)

INCLUDES = -Iinclude
DEFINES =
CFLAGS = -O2 -Wall -Werror -pedantic -std=c99 $(INCLUDES) $(DEFINES)
LDFLAGS =
ifeq ($(UNAME),Darwin)
LDLIBS = -lglfw -framework OpenGL
else
LDLIBS = -lglfw -lGL -ldl
endif

SOURCES := $(shell find src -name *.c)
OBJECTS := $(SOURCES:%=build/%.o)

all: nimbus

nimbus: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

build/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -rf $(OBJECTS) nimbus

.PHONY: clean

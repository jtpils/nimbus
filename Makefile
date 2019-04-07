CC = gcc

INCLUDES =
DEFINES =
CFLAGS = -O2 -Wall -Werror -pedantic -std=c99 $(INCLUDES) $(DEFINES)
LDFLAGS =
LDLIBS = -lglfw -framework OpenGL

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

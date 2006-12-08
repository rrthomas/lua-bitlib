# makefile for bitlib

# Set Lua version (typically lua50 or lua5.1)
LUA=lua5.1

CFLAGS += -W -Wall -O2 -fPIC -I/usr/include/$(LUA)

OBJS=lbitlib.o
SRCS=lbitlib.c
AR=ar rcu

LIB=bit
T=$(LIB).a
V=0

all: $T

# shared libraries (for Linux)
so: $T
	$(CC) $(CFLAGS) -o $(LIB).so.$V -shared *.o -l$(LUA)
	ln -s $(LIB).so.$V $(LIB).so

$T: $(OBJS)
	$(AR) $@ $(OBJS)

clean:
	rm -f $(OBJS) $T *.so*

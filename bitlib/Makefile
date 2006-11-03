# makefile for bitlib for Lua 5.1

CFLAGS += -W -Wall -O2 -fPIC -I/usr/include/lua5.1

OBJS=lbitlib.o
SRCS=lbitlib.c
AR=ar rcu

LIB=bit
T=$(LIB).a
V=0

all: $T

# shared libraries (for Linux)
so: $T
	$(CC) $(CFLAGS) -o $(LIB).so.$V -shared *.o -llua5.1
	ln -s $(LIB).so.$V $(LIB).so

$T: $(OBJS)
	$(AR) $@ $(OBJS)

clean:
	rm -f $(OBJS) $T *.so*

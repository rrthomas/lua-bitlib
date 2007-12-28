## Process this file with automake to produce Makefile.in

lualib_LTLIBRARIES = bit.la

bit_la_SOURCES = lbitlib.c
bit_la_LDFLAGS = -module

EXTRA_DIST = test.lua

check:
	libtool --mode=execute -dlopen bit.la shake $(top_srcdir)/test.lua

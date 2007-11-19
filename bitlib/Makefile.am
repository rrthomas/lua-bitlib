## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = bit.la

bit_la_SOURCES = lbitlib.c
bit_la_LDFLAGS = -module

EXTRA_DIST = testbit.lua

# FIXME: Setting of package.cpath only works because LD_LIBRARY_PATH
# contains only a single directory in this case
check:
	libtool --mode=execute -dlopen bit.la lua -e 'package.path="";package.cpath=os.getenv("LD_LIBRARY_PATH") .. "/?.so"' $(top_srcdir)/testbit.lua

#
# Copyright (C) 2013-2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
#
# makefile - Builds My C Library.
#

# Directories.
export PREFIX = ~
export INCDIR = $(CURDIR)/include
export LIBDIR = $(CURDIR)/lib
export SRCDIR = $(CURDIR)/src

# Library file.
export LIB = libmylibc.a

# Toolchain.
export CC = gcc
export AR = ar

# Toolchain configuration.
export OPTIMIZATION = -D NDEBUG -O3
export DEBUG = -g
export CFLAGS = -I $(INCDIR) -ansi -pedantic -Wall -Wextra -Werror
export ARFLAGS = -vq

# Builds everything.
all: release

# Installs mylibc.
install: release
	mkdir -p $PREFIX/include/mylibc
	mkdir -p $PREFIX/lib
	cp $(LIBDIR)/$(LIB) $PREFIX/lib/
	cp $(INCDIR)/* $PREFIX/include/mylibc

# Uninstalls mylibc.
uninstall:
	rm -f $PREFIX/lib/$(LIB)
	rm -R -f $PREFIX/include/mylibc

# Builds release version.
release:
	mkdir -p lib
	cd $(SRCDIR) && $(MAKE) release

# Cleans compilation files.
clean:
	cd $(SRCDIR) && $(MAKE) clean

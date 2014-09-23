#
# Copyright(C) 2014 Pedro H. Penna  <pedrohenriquepenna@gmail.com>,
#                   Larissa Leijôto <larissa.leijoto@gmail.com>
#

# Directories.
export BINDIR    = $(CURDIR)/bin
export INCDIR    = $(CURDIR)/include
export LIBDIR    = $(CURDIR)/lib
export LIBSRCDIR = $(CURDIR)/libsrc
export SRCDIR    = $(CURDIR)/src

# Libraries.
export LIBS = libmylibc.a -lm

# Toolchain.
export CC = gcc
export AR = ar

# Toolchain configuration.
export OPTIMIZATION = -D NDEBUG -O3
export CFLAGS = -I $(INCDIR) -ansi -pedantic -Wall -Wextra -Werror

# Builds everything.
all: libraries

# Builds libraries.
libraries:
	cd $(LIBSRCDIR) && $(MAKE) all

# Cleans compilation files.
clean:
	cd $(LIBSRCDIR) && $(MAKE) clean

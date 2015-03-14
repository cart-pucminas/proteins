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
export LIBS = $(LIBDIR)/libmylibc.a -lm

# Executable name.
export EXEC = predict

# Toolchain.
export CC = gcc
export AR = ar

# Toolchain configuration.
export OPTIMIZATION = -D NDEBUG -O3
export CFLAGS = -I $(INCDIR) -ansi -pedantic -Wall -Wextra -Werror -std=c99

# Builds everything.
all: libraries
	mkdir -p $(BINDIR)
	cd $(SRCDIR) && $(MAKE) all

# Builds libraries.
libraries:
	mkdir -p $(LIBDIR)
	cd $(LIBSRCDIR) && $(MAKE) all

# Cleans compilation files.
clean:
	cd $(LIBSRCDIR) && $(MAKE) clean

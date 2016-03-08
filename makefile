#
# Copyright(C) 2014 Pedro H. Penna  <pedrohenriquepenna@gmail.com>,
#                   Larissa Leijôto <larissa.leijoto@gmail.com>
#

# Directories.
export PREFIX     = $(CURDIR)
export BINDIR     = $(CURDIR)/bin
export CONTRIBDIR = $(CURDIR)/contrib
export INCDIR     = $(CURDIR)/include
export LIBDIR     = $(CURDIR)/lib
export LIBSRCDIR  = $(CURDIR)/libsrc
export SRCDIR     = $(CURDIR)/src

# Libraries.
export MYLIB = mylib-0.7
export LIBS += $(LIBDIR)/libmy.a
export LIBS += $(LIBDIR)/libsvm.a
export LIBS += -lm

# Executable name.
export EXEC = predict

# Toolchain.
export CXX = g++
export CC  = gcc
export AR  = ar

# Toolchain configuration.
CXXFLAGS= -D NDEBUG -O3
export CFLAGS = -I $(INCDIR) -ansi -pedantic -Wall -Wextra -Werror -std=c99
export CFLAGS += -D NDEBUG -O3

# Builds everything.
all: libraries
	mkdir -p $(BINDIR)
	cd $(SRCDIR) && $(MAKE) all

# Builds libraries.
libraries:
	mkdir -p $(LIBDIR)
	cd $(CONTRIBDIR) &&                                \
	mkdir -p $(MYLIB) &&                               \
	tar -xjvf $(MYLIB).tar.bz2 --directory $(MYLIB) && \
	cd $(MYLIB) &&                                     \
	$(MAKE) install PREFIX=$(PREFIX)
	rm -rf $(CONTRIBDIR)/$(MYLIB)
	cd $(LIBSRCDIR) && $(MAKE) all
	cd $(LIBSRCDIR) && $(MAKE) all

# Cleans compilation files.
clean:
	cd $(LIBSRCDIR) && $(MAKE) clean
	cd $(SRCDIR) && $(MAKE) clean
	rm -rf $(INCDIR)/mylib
	rm -rf $(LIBDIR)

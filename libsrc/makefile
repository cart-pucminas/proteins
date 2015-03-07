#
# Copyright(C) 2014 Pedro H. Penna  <pedrohenriquepenna@gmail.com>,
#                   Larissa Leijôto <larissa.leijoto@gmail.com>
#

# Phony list.
.PHONY: mylibc
.PHONY: libsvm

# Builds everything.
all: mylibc libsvm

# Builds My C Library.
mylibc:
	cd mylibc/ && $(MAKE) install PREFIX=$(CURDIR)/..
	
# Builds SVM library.
libsvm:
	cd libsvm/ && $(MAKE) all

# Cleans compilation files.
clean:
	cd mylibc/ && $(MAKE) uninstall PREFIX=$(CURDIR)/..
	cd libsvm/ && $(MAKE) clean

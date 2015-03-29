#
# Copyright(C) 2014 Pedro H. Penna  <pedrohenriquepenna@gmail.com>,
#                   Larissa Leijôto <larissa.leijoto@gmail.com>
#

# Phony list.
.PHONY: mylib
.PHONY: libsvm

# Builds everything.
all: mylib libsvm

# Builds My C Library.
mylib:
	cd mylib/ && $(MAKE) install PREFIX=$(CURDIR)/..
	
# Builds SVM library.
libsvm:
	cd libsvm/ && $(MAKE) all

# Cleans compilation files.
clean:
	cd mylib/ && $(MAKE) uninstall PREFIX=$(CURDIR)/..
	cd libsvm/ && $(MAKE) clean

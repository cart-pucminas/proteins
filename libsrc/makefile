#
# Copyright(C) 2014 Pedro H. Penna  <pedrohenriquepenna@gmail.com>,
#                   Larissa Leijôto <larissa.leijoto@gmail.com>
#

# Phony list.
.PHONY: mylib
.PHONY: libsvm

# Builds everything.
all: libsvm

# Builds SVM library.
libsvm:
	cd libsvm/ && $(MAKE) all

# Cleans compilation files.
clean:
	cd libsvm/ && $(MAKE) clean

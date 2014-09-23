#
# Copyright(C) 2014 Pedro H. Penna  <pedrohenriquepenna@gmail.com>,
#                   Larissa Leijôto <larissa.leijoto@gmail.com>
#

# Phony list.
.PHONY: mylibc

# Builds everything.
all: mylibc

# Builds My C Library.
mylibc:
	cd mylibc/ && $(MAKE) install PREFIX=$(CURDIR)/..

# Cleans compilation files.
clean:
	cd mylibc/ && $(MAKE) uninstall PREFIX=$(CURDIR)/..

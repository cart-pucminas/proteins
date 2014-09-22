#
# Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
#

# Builds everything.
all: release debug

# Builds release version.
release:
	cd ai && $(MAKE) release
	cd algorithm && $(MAKE) release
	cd array && $(MAKE) release
	cd graph && $(MAKE) release
	cd list && $(MAKE) release
	cd matrix && $(MAKE) release
	cd object && $(MAKE) release
	cd pqueue && $(MAKE) release
	cd table && $(MAKE) release
	cd util && $(MAKE) release
	cd vector && $(MAKE) release

# Builds debug version.
debug:
	cd ai && $(MAKE) debug
	cd algorithm && $(MAKE) debug
	cd array && $(MAKE) debug
	cd graph && $(MAKE) debug
	cd list && $(MAKE) debug
	cd matrix && $(MAKE) debug
	cd object && $(MAKE) debug
	cd pqueue && $(MAKE) debug
	cd table && $(MAKE) debug
	cd util && $(MAKE) debug
	cd vector && $(MAKE) debug
	
# Cleans compilation files.
clean:
	cd ai && $(MAKE) clean
	cd algorithm && $(MAKE) clean
	cd array && $(MAKE) clean
	cd graph && $(MAKE) clean
	cd list && $(MAKE) clean
	cd matrix && $(MAKE) clean
	cd object && $(MAKE) clean
	cd pqueue && $(MAKE) clean
	cd table && $(MAKE) clean
	cd util && $(MAKE) clean
	cd vector && $(MAKE) clean
	rm -f $(LIBDIR)/$(LIB)

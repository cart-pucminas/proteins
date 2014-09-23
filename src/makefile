#
# Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>,
#                   Larissa Leijôto <larissa.leijoto@gmail.com>
#

# Source files.
SRC = $(wildcard *.c)

# Builds everything.
all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BINDIR)/$(EXEC) $(LIBS)
	
# Cleans compilation files.
clean:
	rm -f $(BINDIR)/$(EXEC)

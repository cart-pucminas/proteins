# Copyright(C) 2015 Pedro H. Penna <pedrohenriquepenna@gmail.com>
#                   Larissa Leijoto <larissa.leijoto@gmail.com>
#
# This file is part of Predict.
#
# Predict is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# Predict is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Predict. If not, see <http://www.gnu.org/licenses/>.

# Source files.
SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

# Builds everything.
all: $(OBJ)
	$(CXX) $(OBJ) -fopenmp  -o $(BINDIR)/$(EXEC) $(LIBS)
	
# Builds object file from C source file.
%.o: %.c
	$(CC) $(CFLAGS) -fopenmp $< -c -o $@
	
# Cleans compilation files.
clean:
	@rm -f $(OBJ)
	@rm -f $(BINDIR)/$(EXEC)

#
# Copyright(C) 2015 Pedro H. Penna  <pedrohenriquepenna@gmail.com>,
#                   Larissa Leijoto <larissa.leijoto@gmail.com>
# 
# This file is part of Proteins.
# 
# Proteins is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
# 
# Proteins is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Proteins. If not, see <http://www.gnu.org/licenses/>.
#

# Source files.
SRC = $(wildcard *.cpp)

# Object files.
OBJ = $(SRC:.cpp=.o)

# Library name.
LIBNAME = libsvm.a

# Builds libsvm.
all: $(OBJ)
	$(AR) $(ARFLAGS) $(LIBDIR)/$(LIBNAME) $^

# Builds object files.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean compilation files.
clean:
	@rm -f $(LIBDIR)/$(LIBNAME)
	@rm -f $(OBJ)
	

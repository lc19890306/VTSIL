# Edit the following variables as needed
# HDF_INSTALL = /usr/local
# EXTLIB = -L$(HDF_INSTALL)/lib
CC          = h5cc
CXX         = h5c++	
CFLAGS      = -O3 -std=c++11
DBGFLAGS    = -O0 -g -ggdb -std=c++11
OBJ         = ./h5_cmprss
# LIB         = -lsz -lz -lm

# INCLUDE   = -I$(HDF_INSTALL)/include
# LIBSHDF   = $(EXTLIB) $(HDF_INSTALL)/lib/libhdf5.a 

all: h5_cmprss

h5_cmprss: h5_cmprss.cpp
	$(CXX) $(CFLAGS) -o $@ h5_cmprss.cpp

debug:
	$(CXX) $(DBGFLAGS) -o $(OBJ) h5_cmprss.cpp

clean: 
	rm -f $(OBJ) *.o 

.SUFFIXES:.o.c

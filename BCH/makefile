# Makefile for BCH program
CXX=g++
CXXFLAGS=-g -std=c++11 
CCLINK=g++
OBJS = BCH.o
RM = rm -f
# Creating the  executable
BCH: $(OBJS)
	$(CCLINK) $(CXXFLAGS) -o BCH $(OBJS)
# Creating the object files
BCH.o: BCH.h BCH.cpp 

# Cleaning old files before new make
clean:
	$(RM) BCH *.o *~ "#"* core.*
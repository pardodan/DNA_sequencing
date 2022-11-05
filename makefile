# Makefile for BCH program
CXX=g++
CXXFLAGS=-g -std=c++11 
CCLINK=g++
OBJS = main.o ReedSolomon.o  BCH.o
#OBJS = main.o ReedSolomon.o  BCH.o encoder_functions.o
RM = rm -f
# Creating the  executable
DSC: $(OBJS)
	$(CCLINK) $(CXXFLAGS) -o DSC $(OBJS)
# Creating the object files
#main.o: main.cpp  ReedSolomon.h BCH.h encoder_functions.h
main.o: main.cpp  ReedSolomon.h BCH.h
BCH.o: BCH.h BCH.cpp
ReedSolomon.o: ReedSolomon.h ReedSolomon.cpp
#encoder_functions.o: encoder_functions.cpp encoder_functions.h
# Cleaning old files before new make
clean:
	$(RM) DSC *.o *~ "#"* core.*
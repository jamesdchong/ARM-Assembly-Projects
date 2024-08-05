#
# Makefile for CSE 30 -- PAMT 
#

HEADERS		= pamt.h

CPP_SRCS	= numOfFactors.cpp main.cpp 

CPP_OBJS	= numOfFactors.o main.o

OBJS		= ${CPP_OBJS}

EXE		= pamt

#
# Relevant man pages:
#
# man -M /software/common/gnu/man g++
#

GCC		= g++

GCC_FLAGS	= -O3 -lpthread -c -Wall -std=c++11
LD_FLAGS	= -lpthread -Wall

#
# Standard rules
#

.cpp.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OBJS)
	@echo ""
	@echo "Done."

${CPP_OBJS}:      $(HEADERS)

clean:
	@echo "Cleaning up project directory ..."
	rm -f *.o $(EXE) *.ln core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make


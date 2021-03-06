# Sample Makefile for CMSC 23700 Project 2
#
# This makefile assumes that your program consists of
# a single source file named "main.c".
#

TARGET =	tracer

SHELL =		/bin/sh
OS =		$(shell uname -s)

# the location of doxygen depends on the system that you are running,
# but you may have to edit this path.
#
ifeq ($(OS),Darwin)
  DOXYGEN =	/Applications/Doxygen.app/Contents/Resources/doxygen
else
  DOXYGEN =	/usr/bin/doxygen
endif

CC =		gcc --std=gnu99
CFLAGS =	-Wall -pedantic -ggdb
LDFLAGS =	-lm -lxml2

# where to find the source code
#
VPATH =		../src ../src/engine ../src/objects ../src/objects/primitives ../src/engine/EasyBMP

SRCS =		$(wildcard ../src/*.c) $(wildcard ../src/engine/*.c) $(wildcard ../src/objects/*.c) $(wildcard ../src/objects/primitives/*.c) 
INCLUDES =	$(wildcard ../src/*.h) $(wildcard ../src/engine/*.h) $(wildcard ../src/objects/*.h) $(wildcard ../src/objects/primitives/*.h)
DOC_SRCS =	$(SRCS) $(INCLUDES) ../main-page

OBJS =		$(notdir $(SRCS:.c=.o)) 

$(TARGET):	$(OBJS) $(CPPOBJS) .depend
	g++ $(CFLAGS) -o $(TARGET) $(OBJS) $(CPPOBJS) $(LDFLAGS)

.PHONY:		doc
doc:		../doc

../doc:		$(DOC_SRCS)
	(cd ..; $(DOXYGEN) Doxyfile)
	- touch ../doc

# include-file dependency information
#
.depend:	$(SRCS) $(INCLUDES) 
	- $(CC) $(CFLAGS) $(CPPFLAGS) -MM $(SRCS) > .depend

# cleanup by removing generated files
#
.PHONY:		clean
clean:
		rm -rf *.o $(TARGET) ../doc .depend


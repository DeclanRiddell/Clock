# Makefile for the clock project
#
# Darren Provine, 17 July 2009

PROGRAM = clock
SOURCES = clock.c model.c view.c
OBJECTS = clock.o model.o view.o
DRIVERS = LEDisplay.o
INCLUDE = -I/usr/lib/gcc/x86_64-redhat-linux/3.4.6/include
LIBRARY = -lncurses
CFLAGS  = -g -Wall
COMPILER= gcc

.SUFFIXES:
.SUFFIXES: .c .o

.c.o: ; $(COMPILER) $(CFLAGS) -c $< $(INCLUDE)

$(PROGRAM) : $(OBJECTS)
	$(COMPILER) -o $(PROGRAM) $(CFLAGS) $(OBJECTS) $(DRIVERS) $(LIBRARY)

clean: ; /bin/rm -f $(PROGRAM) $(OBJECTS) depend

# handle dependencies
depend : $(SOURCES)
	gcc -M $(SOURCES) > depend

include depend

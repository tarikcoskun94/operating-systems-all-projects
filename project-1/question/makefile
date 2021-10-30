IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

PROGRAMS := MakeCopy ForkCopy PipeCopy CompareTime MyShell MoreShell DupShell

all: $(PROGRAMS)

ODIR=./
LDIR =../lib

LIBS=-lm

_DEPS = Prj1header.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

########################

_OBJ = MakeCopy.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

MakeCopy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

########################

_OBJ = ForkCopy.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

ForkCopy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

########################

_OBJ = PipeCopy.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

PipeCopy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

########################

_OBJ = CompareTime.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

CompareTime: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

########################

_OBJ = MyShell.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

MyShell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

########################

_OBJ = MoreShell.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

MoreShell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

########################

_OBJ = DupShell.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

DupShell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
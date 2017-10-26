# OUTPUT BINARY NAME
BINFILE := rbs1

# TARGET DIRECTORIES
SDIR 	:= src
ODIR 	:= obj
LDIR 	:= lib
BDIR 	:= bin
IDIR 	:= include

# COMPILER PARAMETERS
CC 		:= gcc
CFLAGS 	:= -I$(IDIR) -O2 -Wall --std=c99 -m64 # -Wstrict-prototypes -Wmissing-prototypes -pedantic -Wshadow -Wpointer-arith -Wcast-qual 
LIBS 	:= -lm
PCH 	:= $(IDIR)/stdafx.h

# SOURCE FILES
DEPS 	:= $(shell find $(IDIR) -name '*.h')
SOURCES := $(shell find $(SDIR) -name '*.c')
OBJ 	:= $(addprefix $(ODIR)/, $(SOURCES:$(SDIR)/%.c=%.o))

.PHONY: clean run all

all: $(BDIR)/$(BINFILE)

$(PCH).gch: $(PCH)
	$(CC) -c $< -o $@ $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS) $(PCH).gch
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/$(BINFILE): $(OBJ)
	mkdir -p $(BDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	find $(ODIR) -type f -name '*.o' -delete -print
	rm -rf $(BDIR)/* -v
	rm $(PCH).gch

run: $(BDIR)/$(BINFILE)
	(cd $(BDIR); ./$(BINFILE))
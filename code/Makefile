# OUTPUT BINARY NAME
BINFILE = rbs1

# TARGET DIRECTORIES
SDIR = src
ODIR = obj
LDIR = lib
BDIR = bin
IDIR = include

# COMPILER PARAMETERS
CC = gcc
CFLAGS = -I$(IDIR) -O2 -Wall --std=c99
LIBS = -lm

# SOURCE FILES
DEPS := $(shell find $(IDIR) -name '*.h')
SOURCES := $(shell find $(SDIR) -name '*.c')
OBJ := $(addprefix $(ODIR)/, $(SOURCES:$(SDIR)/%.c=%.o))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/$(BINFILE): $(OBJ)
	mkdir -p $(BDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean run

clean:
	find $(ODIR) -type f -name '*.o' -delete
	rm -rf $(BDIR)/*

run: $(BDIR)/$(BINFILE)
	(cd $(BDIR); ./$(BINFILE))
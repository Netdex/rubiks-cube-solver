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
CFLAGS = -I$(IDIR) -O2 -Werror -Wall --std=c99
LIBS = -lm

# SOURCE FILES
DEPS := $(shell find $(IDIR) -name '*.h')
SOURCES := $(shell find $(SDIR) -name '*.c')
OBJ := $(addprefix $(ODIR)/, $(SOURCES:$(SDIR)/%.c=%.o))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINFILE): $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	find $(ODIR) -type f -name '*.o' -delete

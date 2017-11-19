# OUTPUT BINARY NAME
BINFILE := ../libBBBio.a

# TARGET DIRECTORIES
SDIR 	:= src
ODIR 	:= obj
IDIR 	:= include

# COMPILER PARAMETERS
#TOOLCHAIN := 
DEF		:= -D_POSIX_C_SOURCE=200809L
CFLAGS 	:= -I$(IDIR) -Wall --std=c99 $(DEF) -O2

# SOURCE FILES
DEPS 	:= $(shell find $(IDIR) -name '*.h')
SOURCES := $(shell find $(SDIR) -name '*.c')
OBJ 	:= $(addprefix $(ODIR)/, $(SOURCES:$(SDIR)/%.c=%.o))

.PHONY: clean run all

all: $(BINFILE)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	mkdir -p $(dir $@)
	$(TOOLCHAIN)gcc -c -o $@ $< $(CFLAGS)

$(BINFILE): $(OBJ)
	$(TOOLCHAIN)ar rcs $@ $^

clean:
	find $(ODIR) -type f -name '*.o' -delete -print
	rm -rf $(BINFILE) -v


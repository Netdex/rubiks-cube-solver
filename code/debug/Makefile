# OUTPUT BINARY NAME
BINFILE := rbs1d

# TARGET DIRECTORIES
SDIR 	:= src
ODIR 	:= obj
LDIR 	:= ../lib
BDIR 	:= bin
IDIR 	:= include

LBBBIODIR  := $(LDIR)/BBBiolib
LBBBIOIDIR := $(LBBBIODIR)/include
LBBBIOLIB  := $(LDIR)/libBBBio.a

# COMPILER PARAMETERS
# TOOLCHAIN := 
DEF		:= -D_POSIX_C_SOURCE=200809L
INC 	:= -I$(IDIR) -I$(LBBBIOIDIR)
CFLAGS 	:= $(INC) $(DEF) -Wall --std=c99 -O2 
LIBS 	:= -L$(LDIR) -lm -lBBBio -lncurses -lpthread -ltinfo

# SOURCE FILES
DEPS 	:= $(shell find $(IDIR) -name '*.h')
SOURCES := $(shell find $(SDIR) -name '*.c')
OBJ 	:= $(addprefix $(ODIR)/, $(SOURCES:$(SDIR)/%.c=%.o))

.PHONY: clean run all

all: $(BDIR)/$(BINFILE)

$(LBBBIOLIB):
	$(MAKE) -C $(LBBBIODIR)
	
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	mkdir -p $(dir $@)
	$(TOOLCHAIN)gcc -c -o $@ $< $(CFLAGS)

$(BDIR)/$(BINFILE): $(OBJ) $(LBBBIOLIB)
	mkdir -p $(BDIR)
	$(TOOLCHAIN)gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	find $(ODIR) -type f -name '*.o' -delete -print
	rm -rf $(BDIR)/* -v
	#$(MAKE) -C $(LBBBIODIR) clean

run: $(BDIR)/$(BINFILE)
	(cd $(BDIR); ./$(BINFILE))

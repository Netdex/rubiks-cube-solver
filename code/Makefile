# OUTPUT BINARY NAME
BINFILE := rbs1

# TARGET DIRECTORIES
SDIR 	:= src
ODIR 	:= obj
LDIR 	:= lib
BDIR 	:= bin
IDIR 	:= include

LBBBIODIR  := $(LDIR)/BBBiolib
LBBBIOIDIR := $(LBBBIODIR)/include
LBBBIOLIB  := $(LDIR)/libBBBio.a

# COMPILER PARAMETERS
# TOOLCHAIN := 
DEF		:= -D_POSIX_C_SOURCE=200809L -DLOG_USE_COLOR #-DNO_GPIO
INC 	:= -I$(IDIR) -I$(LBBBIOIDIR)
CFLAGS 	:= $(INC) $(DEF) -Wall --std=c99 -O2 # -m64 -Wstrict-prototypes -Wmissing-prototypes -pedantic -Wshadow -Wpointer-arith -Wcast-qual 
LIBS 	:= -L$(LDIR) -lm -lBBBio
PCH 	:= $(IDIR)/stdafx.h

# SOURCE FILES
DEPS 	:= $(shell find $(IDIR) -name '*.h')
SOURCES := $(shell find $(SDIR) -name '*.c')
OBJ 	:= $(addprefix $(ODIR)/, $(SOURCES:$(SDIR)/%.c=%.o))

.PHONY: clean run all

all: $(BDIR)/$(BINFILE)

# COMPILE EXTERNAL BBBIOLIB
$(LBBBIOLIB):
	$(MAKE) -C $(LBBBIODIR)

# PRECOMPIELD HEADER
$(PCH).gch: $(PCH)
	$(TOOLCHAIN)gcc -c $< -o $@ $(CFLAGS)

# OBJECT FILES
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS) $(PCH).gch
	mkdir -p $(dir $@)
	$(TOOLCHAIN)gcc -c -o $@ $< $(CFLAGS)

# BINARY FILE
$(BDIR)/$(BINFILE): $(OBJ) $(LBBBIOLIB)
	mkdir -p $(BDIR)
	$(TOOLCHAIN)gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	find $(ODIR) -type f -name '*.o' -delete -print
	rm -rf $(BDIR)/* -v
	rm -f $(PCH).gch
	#$(MAKE) -C $(LBBBIODIR) clean

run: $(BDIR)/$(BINFILE)
	(cd $(BDIR); ./$(BINFILE))

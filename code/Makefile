BINFILE = rbs1

SDIR = src
ODIR = obj
LDIR = lib
BDIR = bin
IDIR = include

CC = gcc
CFLAGS = -I$(IDIR) -O2 -Werror -Wall
LIBS = -lm

DEPS = $(wildcard $(IDIR)/*.h)
SOURCES = $(notdir $(wildcard $(SDIR)/*.c))
OBJ = $(addprefix $(ODIR)/, $(SOURCES:.c=.o))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINFILE): $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -rf $(ODIR)\*.o

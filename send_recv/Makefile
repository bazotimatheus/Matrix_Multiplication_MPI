CC=mpicc
CFLAGS=
LIBS=

SDIR=src
LDIR=lib
ODIR=obj

# Seta os arquivos fontes e gera os objetos
_SRCS=multmatriz.c main.c
SRCS=$(patsubst %,$(SDIR)/%,$(_SRCS))

_DEPS=multmatriz.h
DEPS=$(patsubst %,$(LDIR)/%,$(_DEPS))

_OBJS=$(_SRCS:.c=.o)
OBJS=$(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o:$(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

# Cria o executavel "multmatriz"
multmatriz: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Limpa a casa
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ multmatriz

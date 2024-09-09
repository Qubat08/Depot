# Compiler
NVCC = nvcc

# Dossiers
SRCDIR = src
INCDIR = include
BUILDDIR = build
BINDIR = bin

# Fichiers sources
SRCEXT = cu
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Nom de l'exécutable
EXECUTABLE = main

# Options de compilation
CFLAGS = -I$(INCDIR) -O3 -lm

# Règle par défaut
all: $(EXECUTABLE)

# Règle pour construire l'exécutable
$(EXECUTABLE): $(BINDIR)/$(EXECUTABLE)
	mv $< .

$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(NVCC) $^ -o $@ $(CFLAGS)

# Règle pour construire les fichiers objets
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(NVCC) $(CFLAGS) -c $< -o $@

# Règle de nettoyage
clean:
	rm -rf $(BUILDDIR) $(BINDIR)/$(EXECUTABLE) $(EXECUTABLE)
	rm -rf $(BINDIR)

# Règle de nettoyage complet
distclean: clean
	rm -rf $(BINDIR)

.PHONY: all clean distclean

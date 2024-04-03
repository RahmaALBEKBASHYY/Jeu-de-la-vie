# General Infos
TARGET = main
AUTHORFIRST = Samy
AUTHORLAST = Mosa
VERSION = $(shell [ -d .git ] && git describe --tags --abbrev=0)

# Directories
BINDIR = bin
DOCDIR = doc
INCLUDEDIR = include
LIBDIR = lib
OBJDIR = obj
SRCDIR = src

# Archive 
ARCHIVE = $(AUTHORLAST)$(AUTHORFIRST)-GoL-$(VERSION).tar.xz
ARCHIVE_FILES = $(SRCDIR) $(INCLUDEDIR) Makefile Doxyfile doxygen-awesome.css

# Library
LIBJEU = libjeu.a
LIBOBJ = $(OBJDIR)/jeu.o $(OBJDIR)/grille.o

# Commands
CC = gcc
RM = rm -f

# Flags
CFLAGS = -Wall -g -I$(INCLUDEDIR)
LDFLAGS = -L$(LIBDIR)
LDLIBS = -ljeu

# Files
OBJECTS = $(OBJDIR)/main.o
INCLUDES = $(wildcard $(INCLUDEDIR)/*.h)

# Mode
LAST_MODE=$(shell [ -f .mode ] && cat .mode)
ifneq ($(MODE), $(LAST_MODE))
	EXTRAS += clean mode
endif

ifeq ($(MODE), TEXTE)
	OBJECTS += $(OBJDIR)/io.o
else
	CFLAGS += -I/usr/include/cairo -I/usr/include/fontconfig -D MODE_GRAPHIQUE
	LDLIBS += -lcairo -lm -lX11 -lfontconfig
	OBJECTS += $(OBJDIR)/io_g.o
endif

# Rules
$(BINDIR)/$(TARGET): $(EXTRAS) $(LIBDIR)/$(LIBJEU) $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@ $(LDLIBS)

$(LIBDIR)/$(LIBJEU): $(LIBOBJ)
	@mkdir -p $(LIBDIR)
	ar -rcs $@ $^

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean dist docs mode
all : $(BINDIR)/$(TARGET)

clean:
	$(RM) $(OBJDIR)/* $(BINDIR)/* $(LIBDIR)/*
	$(RM) -r $(DOCDIR)/*
	$(RM) $(ARCHIVE)

dist:
	tar -Jcvf $(ARCHIVE) $(ARCHIVE_FILES) README.md

docs:
	doxygen Doxyfile

mode:
	@echo $(MODE) > .mode

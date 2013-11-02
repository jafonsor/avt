EXE = assignment2

BINDIR = bin
OBJSDIR = objs
SRCSDIR = src
SHADER_DIR = shaders


DIRS1 = $(shell cd ../$(SRCSDIR); find . -type d)
DIRS3 = $(filter-out ./$(SHADER_DIR), $(DIRS1))
DIRS4 = $(filter-out ., $(DIRS3))
MKDIRS = $(DIRS4:./%=mkdir -p %)


mk-subsrc:
	(cd ../$(OBJSDIR);$(MKDIRS))

mv-shaders:
	rm -rf ../$(BINDIR)/shaders
	mkdir ../$(BINDIR)/shaders
	cp -r ../$(SRCSDIR)/shaders/* ../$(BINDIR)/shaders

debian: mk-subsrc
	cp debian-make/makefile ../
	(cd ../; \
	make release EXE=$(EXE) BINDIR=$(BINDIR) OBJSDIR=$(OBJSDIR) SRCSDIR=$(SRCSDIR); \
	rm makefile)

ubuntu: mk-subsrc
	cp ubuntu-make/makefile ../
	(cd ../; \
	make release EXE=$(EXE) BINDIR=$(BINDIR) OBJSDIR=$(OBJSDIR) SRCSDIR=$(SRCSDIR); \
	rm makefile)
	
run: mv-shaders
	(cd ../$(BINDIR); ./$(EXE))

clean:
	(cd ../$(OBJSDIR); rm -rf *;)
	rm -f ../$(BINDIR)/$(EXE)

deliver: clean
	rm -f *~
	(cd $(SRCSDIR); rm -f *~)

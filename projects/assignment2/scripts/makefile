EXE = assignment2

BINDIR = bin
OBJSDIR = objs
SRCSDIR = src

mv-shaders:
	rm -rf ../$(BINDIR)/shaders
	mkdir ../$(BINDIR)/shaders
	cp -r ../$(SRCSDIR)/shaders/* ../$(BINDIR)/shaders

debian:
	cp debian-make/makefile ../
	(cd ../; \
	make release EXE=$(EXE) BINDIR=$(BINDIR) OBJSDIR=$(OBJSDIR) SRCSDIR=$(SRCSDIR); \
	rm makefile)

ubuntu:
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

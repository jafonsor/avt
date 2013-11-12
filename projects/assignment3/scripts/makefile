EXE = assignment3

BINDIR = bin
OBJSDIR = objs
SRCSDIR = src

debian-test:
	cp debian-make/makefile ../
	(cd ../; \
	make test EXE=$(EXE) BINDIR=$(BINDIR) OBJSDIR=$(OBJSDIR) SRCSDIR=$(SRCSDIR); \
	rm makefile)

ubuntu-test: $(OBJS_WITH_DIR)
	cp ubuntu-make/makefile ../
	(cd ../; \
	make test EXE=$(EXE) BINDIR=$(BINDIR) OBJSDIR=$(OBJSDIR) SRCSDIR=$(SRCSDIR); \
	rm makefile)


debian: 
	cp debian-make/makefile ../
	(cd ../; \
	make release EXE=$(EXE) BINDIR=$(BINDIR) OBJSDIR=$(OBJSDIR) SRCSDIR=$(SRCSDIR); \
	rm makefile)

ubuntu: $(OBJS_WITH_DIR)
	cp ubuntu-make/makefile ../
	(cd ../; \
	make release EXE=$(EXE) BINDIR=$(BINDIR) OBJSDIR=$(OBJSDIR) SRCSDIR=$(SRCSDIR); \
	rm makefile)
	
run:
	./../$(BINDIR)/$(EXE)

clean:
	(cd ../$(OBJSDIR); rm -rf *;)
	rm -f ../$(BINDIR)/$(EXE)

deliver: clean
	rm -f *~
	(cd $(SRCSDIR); rm -f *~)

STUDENT_NUM = 69408
PROJSDIR = projects
BINDIR = $(PROJSDIR)/bin
NEWPROJDIR = ../$(PROJSDIR)/$(projname)

all: build-assignment1

clean: clean-assignment1

# creates a zip file with the AVT directory cleaned
deliver: deliver-assignment1
	rm -f *~ 
	(cd ../../; rm -f AL_*.zip; zip -r AL_$(name)_$(STUDENT_NUM) AVT)
	

# assignment1
build-assignment1:
	(cd ../$(PROJSDIR)/assignment1/scripts; make release)
	
run-assignment1: 
	(cd ../$(PROJSDIR)/assignment1/scripts; make run)
	
clean-assignment1:
	(cd ../$(PROJSDIR)/assignment1/scripts; make clean)

deliver-assignment1:
	(cd ../$(PROJSDIR)/assignment1/scripts; make deliver)

proj:
	mkdir $(NEWPROJDIR)
	mkdir $(NEWPROJDIR)/scripts
	mkdir $(NEWPROJDIR)/src
	mkdir $(NEWPROJDIR)/src/shaders
	mkdir $(NEWPROJDIR)/objs
	mkdir $(NEWPROJDIR)/bin
	cp -r templateScripts/* $(NEWPROJDIR)/scripts

EXE = assignment1

CC = g++

DEPSDIR = ../../dependencies
DEPS_DEBIAN_DIR = $(DEPSDIR)/debian6
DEPS_UBUNTU_DIR = $(DEPSDIR)/ubuntu13-04

INCLUDES_DEBIAN = -I$(DEPS_DEBIAN_DIR)/glew/include
INCLUDES_UBUNTU = -I$(DEPS_UBUNTU_DIR)/glew/include -I$(DEPS_UBUNTU_DIR)/freeglut/include

LIB_FILE_DEBIAN = -L$(DEPS_DEBIAN_DIR)/glew/lib
LIB_FILE_UBUNTU = -L$(DEPS_UBUNTU_DIR)/glew/lib -L$(DEPS_UBUNTU_DIR)/freeglut/lib

LIBSDEBIAN = -lGL -lGLEW -lglut
LIBSUBUNTU = -lGL -lGLEW -lglut -lX11 -lXxf86vm -lXi

SRCSDIR = src
SRCS = $(shell cd ../$(SRCSDIR); find . -name "*.cpp")
OBJSDIR = objs
OBJS = $(SRCS:%.cpp=%.o)
OBJS_WITH_DIR = $(OBJS:./%.o=$(OBJSDIR)/%.o)
RELEASEDIR = $(OBJSDIR)/Release
DEBUGDIR = $(OBJSDIR)/Debug
BINDIR = ../bin

release-debian: $(OBJS_WITH_DIR)
	(cd ../; $(CC) $(INCLUDES_DEBIAN) $(LIB_FILE_DEBIAN) -o $(EXE) $(OBJS_WITH_DIR) $(LIBSDEBIAN); \
	mv $(EXE) ../$(BINDIR))

release-ubuntu: $(OBJS_WITH_DIR)
	(cd ../; $(CC) $(INCLUDES_UBUNTU) $(LIB_FILE_UBUNTU) -o $(EXE) $(OBJS_WITH_DIR) $(LIBSUBUNTU); \
	mv $(EXE) ../$(BINDIR))

objs/assignment_1.o: ../$(SRCSDIR)/assignment_1.cpp
	g++ -c ../src/assignment_1.cpp

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp
	g++ -c $< -o $@
	
run:
	(cd $(BINDIR); ./$(EXE))

clean:
	(cd $(OBJSDIR); rm -rf Release; rm -rf Debug; mkdir Release; mkdir Debug)
	(cd $(BINDIR); rm -f $(EXE))

deliver: clean
	rm -f *~
	(cd $(SRCSDIR); rm -f *~)

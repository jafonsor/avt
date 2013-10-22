# makefile to compile projects on the lab
CC = g++

DEPSDIR = ../../dependencies
DEPS_DIR = $(DEPSDIR)/ubuntu

INCLUDES = -I$(DEPS_DIR)/glew/include -I$(DEPS_DIR)/freeglut/include
LIB_FILE = -L$(DEPS_DIR)/glew/lib     -L$(DEPS_DIR)/freeglut/lib 

LIBS = -lGL -lGLEW -lglut -lX11 -lXxf86vm -lXi

SRCSDIR = src
SRCS = $(shell cd $(SRCSDIR); find . -name "*.cpp")
OBJSDIR = objs
OBJS = $(SRCS:%.cpp=%.o)
OBJS_WITH_DIR = $(OBJS:./%.o=$(OBJSDIR)/%.o)
RELEASEDIR = $(OBJSDIR)/Release
DEBUGDIR = $(OBJSDIR)/Debug
BINDIR = bin

release: $(OBJS_WITH_DIR)
	$(CC) -o $(EXE) $(OBJS_WITH_DIR) $(LIBS);
	mv $(EXE) $(BINDIR)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp
	g++ -c $< -o $@

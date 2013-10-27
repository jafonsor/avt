# makefile to compile projects on the lab
CC = g++
CFLAGS = -ansi -Wall -pedantic

DEPSDIR = ../../dependencies
DEPS_DIR = $(DEPSDIR)/ubuntu

INCLUDES = -I$(DEPS_DIR)/glew/include -I$(DEPS_DIR)/freeglut/include
LIB_FILE = -L$(DEPS_DIR)/glew/lib     -L$(DEPS_DIR)/freeglut/lib 

LIBS = -lGL -lGLEW -lglut -lGLU -lX11 -lXxf86vm -lXi

SRCS = $(shell cd $(SRCSDIR); find . -name "*.cpp")


OBJSDIR = objs
OBJS = $(SRCS:%.cpp=%.o)
OBJS_WITH_DIR = $(OBJS:./%.o=$(OBJSDIR)/%.o)
RELEASEDIR = $(OBJSDIR)/Release
DEBUGDIR = $(OBJSDIR)/Debug
BINDIR = bin

release: $(OBJS_WITH_DIR)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS_WITH_DIR) $(LIBS);
	mv $(EXE) $(BINDIR)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp
	g++ $(CFLAGS) -c $< -o $@

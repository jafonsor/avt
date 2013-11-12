# makefile to compile projects on the lab
CC = g++
CFLAGS = -ansi -Wall -pedantic
DBUG_FLAGS = -g -ggdb

DEPSDIR = ../../dependencies
DEPS_DIR = $(DEPSDIR)/ubuntu

INCLUDES = -I$(DEPS_DIR)/glew/include -I$(DEPS_DIR)/freeglut/include
LIB_FILE = -L$(DEPS_DIR)/glew/lib     -L$(DEPS_DIR)/freeglut/lib 

LIBS = -lGL -lGLEW -lglut -lGLU -lX11 -lXxf86vm -lXi

SRCS = $(shell cd $(SRCSDIR); find . -name "*.cpp")

OBJSDIR = objs
OBJS = $(SRCS:%.cpp=%.o)
OBJS_WITH_DIRa = $(OBJS:./%.o=$(OBJSDIR)/%.o)
OBJS_WITH_DIR_TEST = $(filter-out %$(EXE).o,$(OBJS_WITH_DIRa))
OBJS_WITH_DIR_EXE  = $(filter-out %test.o, $(OBJS_WITH_DIRa))
RELEASEDIR = $(OBJSDIR)/Release
DEBUGDIR = $(OBJSDIR)/Debug
BINDIR = bin

test: $(OBJS_WITH_DIR_TEST)
	echo $(EXE).o
	$(CC) $(CFLAGS) $(DBUG_FLAGS) -o $(EXE) $(OBJS_WITH_DIR_TEST) $(LIBS);
	mv $(EXE) $(BINDIR)


release: $(OBJS_WITH_DIR_EXE)
	$(CC) $(CFLAGS) $(DBUG_FLAGS) -o $(EXE) $(OBJS_WITH_DIR_EXE) $(LIBS);
	mv $(EXE) $(BINDIR)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp
	g++ $(CFLAGS) $(DBUG_FLAGS) -c $< -o $@

# makefile to compile projects on the lab
CC = g++

DEPSDIR = ../../dependencies
DEPS_DIR = $(DEPSDIR)/debian6

INCLUDES = -I$(DEPS_DIR)/glew/include
LIB_FILE = -L$(DEPS_DIR)/glew/lib

LIBS = -lGL -lGLEW -lglut

SRCSDIR = src
SRCS = $(shell cd $(SRCSDIR); find . -name "*.cpp")
OBJSDIR = objs
OBJS = $(SRCS:%.cpp=%.o)
OBJS_WITH_DIR = $(OBJS:./%.o=$(OBJSDIR)/%.o)
RELEASEDIR = $(OBJSDIR)/Release
DEBUGDIR = $(OBJSDIR)/Debug
BINDIR = bin

release: $(OBJS_WITH_DIR)
	$(CC) $(INCLUDES) $(LIB_FILE) -o $(BINDIR)/$(EXE) $(OBJS_WITH_DIR) $(LIBS);
	mv $(EXE) $(BINDIR)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp
	g++ -c $< -o $@ $(INCLUDES)

# makefile to compile projects on the lab
CC = g++

DEPSDIR = ../../dependencies
DEPS_DIR = $(DEPSDIR)/debian6

INCLUDES = -I$(DEPS_DIR)/glew/include
LIB_FILE = -L$(DEPS_DIR)/glew/lib

LIBS = -lGL -lGLEW -lGLU -lglut

SRCSDIR = src
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
	$(CC) $(INCLUDES) $(LIB_FILE) $(CFLAGS) $(DBUG_FLAGS) -o $(EXE) $(OBJS_WITH_DIR_EXE) $(LIBS);
	mv $(EXE) $(BINDIR)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp
	$(CC) $(INCLUDES) $(LIB_FILE)$(CFLAGS) $(DBUG_FLAGS) -c $< -o $@

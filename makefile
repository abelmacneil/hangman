VPATH=./src:./src/include
SRCDIR=src
BUILDDIR=obj
BINDIR=bin
CC=g++
LIBS=
CFLAGS=-O3 -Wall
INCLUDE=-I src/include 
MAIN=hangman
MAINBIN=$(BINDIR)/$(MAIN)
SRCS=hangman.cpp cpu.cpp game.cpp
#OBJS=$(MAIN).o cpu.o game.o
OBJS=$(SRCS:%.cpp=$(BUILDDIR)/%.o)

compile : mkdirs $(MAINBIN)

$(MAINBIN)	: $(OBJS)
	echo $(INCLUDE)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(INCLUDE) -o $(MAINBIN)

hangman.o	: cpu.o game.o
cpu.o		: cpu.hpp cpu.cpp
game.o		: game.hpp game.cpp

#-------------------------------------------------------------

run: compile
	$(MAINBIN)

clean:
	rm -r $(BUILDDIR)
	rm -r $(BINDIR)

mkdirs:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)

build: clean compile	

lines :
	wc -l `find $(SRCDIR) -type f` | sort -nk 1
	
$(BUILDDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

#=============================================================#

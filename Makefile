CC = g++
ASM = nasm
LD = g++

LUA_DIR = D:/Programming/unknown-game/lua-5.3.5/src
SFML_DIR= C:/SFML
SFML_LIB_DIR= $(SFML_DIR)/lib
INCDIR = $(SFML_DIR)/include

CFLAGS = -c -g -O3 -Wall -I$(INCDIR) -I$(LUA_DIR)
AFLAGS = -f elf64	
LDFLAGS = -g -no-pie
SFML = -lsfml-graphics -lsfml-window -lsfml-system 

VPATH = ./src
OBJPATH = ./compile

SRCC = luaScript.cpp main.cpp game.cpp 									 gameobjects.cpp animation.cpp gamestate.cpp menustate.cpp
HEAD = luaScript.hpp 		  game.hpp assetmanager.hpp statemanager.hpp gameobjects.hpp animation.hpp state.hpp
SRCSASM =

OBJC = $(SRCC:%.cpp=$(OBJPATH)/%.o)
OBJASM = $(SRCASM:.S=.o)

EXECUTABLE_LINUX = run.out
EXECUTABLE_WINDOWS = run.exe

windows: $(OBJPATH) $(SRCC) $(SRCASM) $(EXECUTABLE_WINDOWS)

linux: $(OBJPATH) $(SRCC) $(SRCASM) $(EXECUTABLE_LINUX)

$(OBJPATH):
	@mkdir $@

$(EXECUTABLE_WINDOWS): $(OBJC)
	@echo "LINKING:"
	$(LD) $(LDFLAGS) $(OBJC) -o  $@ -L$(SFML_LIB_DIR) $(SFML) -L$(LUA_DIR) -llua

$(EXECUTABLE_LINUX): $(OBJC)
	@echo "LINKING:"
	$(LD) $(LDFLAGS) $(OBJC) -o  $@ $(SFML)

$(OBJPATH)/%.o: %.cpp $(HEAD)
	@echo "COMPILING:"
	$(CC) $(CFLAGS) $< -o $@

%.o: %.S
	$(ASM) $(AFLAGS) $< -o $@
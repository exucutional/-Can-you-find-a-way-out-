CC = g++
ASM = nasm
LD = g++
SFML_DIR= C:/SFML
LIBDIR= $(SFML_DIR)/lib
CFLAGS =-c -g -O3 -Wall -I$(SFML_DIR)/include
AFLAGS = -f elf64
LDFLAGS = -g -no-pie
SFML = -lsfml-graphics -lsfml-window -lsfml-system 
VPATH = ./src
OBJPATH = ./compile
SRCC = main.cpp gameobjects.cpp game.cpp
HEAD = gameobjects.hpp game.hpp
SRCSASM = 
OBJC = $(SRCC:%.cpp=$(OBJPATH)/%.o)
OBJASM = $(SRCASM:.S=.o)
EXECUTABLE = run.exe

all: $(OBJPATH) $(SRCC) $(SRCASM) $(EXECUTABLE)

$(OBJPATH):
	@mkdir $@

$(EXECUTABLE): $(OBJC)
	@echo "LINKING:"
	$(LD) $(LDFLAGS) $(OBJC) -o  $@ -L$(LIBDIR) $(SFML)

$(OBJPATH)/%.o: %.cpp $(HEAD)
	@echo "COMPILING:"
	$(CC) $(CFLAGS) $< -o $@

%.o: %.S
	$(ASM) $(AFLAGS) $< -o $@
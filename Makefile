CC = g++
ASM = nasm
LD = g++
CFLAGS =-c -g -O3 -Wall
AFLAGS = -f elf64
LDFLAGS = -g -no-pie
SFML = -lsfml-graphics -lsfml-window -lsfml-system
VPATH = ./src
OBJPATH = ./compile
SRCC = main.cpp Gameobjects.cpp
HEAD = Gameobjects.hpp
SRCSASM = 
OBJC = $(SRCC:%.cpp=$(OBJPATH)/%.o)
OBJASM = $(SRCASM:.S=.o)
EXECUTABLE = run.out

all: $(CMPPATH) $(SRCC) $(SRCASM) $(EXECUTABLE)

$(CMPPATH):
	@mkdir $@

$(EXECUTABLE): $(OBJC)
	@echo "LINKING:"
	$(LD) $(LDFLAGS) $(OBJC) -o  $@ $(SFML)

$(OBJPATH)/%.o: %.cpp $(HEAD)
	@echo "COMPILING:"
	$(CC) $(CFLAGS) $< -o $@

%.o: %.S
	$(ASM) $(AFLAGS) $< -o $@
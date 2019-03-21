BINARY=bin/dfsys.bin
OBJECTS=obj/boot.o				\
		obj/startup.o			\
		obj/termio.o
LNKDATA=src/linker.ld

ASM=yasm
ASMFLAGS=-f elf32

CC=i686-elf-gcc
CFLAGS=-std=c99 -O2 -nostdlib -I./include			\
	   -Wall -Wextra -pedantic						\
	   -ffreestanding -fno-exceptions -fno-rtti

CXX=i686-elf-g++
CXXFLAGS=-std=c++11 -O2	-nostdlib -I./include		\
		 -Wall -Wextra -pedantic					\
		 -ffreestanding -fno-exceptions -fno-rtti

LNK=i686-elf-g++
LNKFLAGS=-O2 -ffreestanding -nostdlib
LNKLIBS=-lgcc

.PHONY: all, clean

all: $(BINARY)

obj/%.o: src/%.s
	@mkdir -p obj
	@printf "[C] $<\n"
	@$(ASM) $(ASMFLAGS) $< -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	@printf "[C] $<\n"
	@$(CC) -c $< -o $@ $(CFLAGS)

obj/%.o: src/%.cpp
	@mkdir -p obj
	@printf "[C] $<\n"
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

$(BINARY): $(OBJECTS) $(LNKDATA)
	@mkdir -p bin
	@printf "[L] $@\n"
	@$(LNK) -T $(LNKDATA) -o $(BINARY) $(LNKFLAGS) $(OBJECTS) $(LNKLIBS)

run: $(BINARY)
	@printf "[E] $(BINARY)\n"
	@qemu-system-x86_64 -kernel $(BINARY)

clean:
	@printf "[R] bin\n"
	@rm -rf bin
	@printf "[R] obj\n"
	@rm -rf obj


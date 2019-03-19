BINARY=bin/dfsys.bin

ASM=nasm
ASMFLAGS=-felf32
CXX=i686-elf-g++
CXXFLAGS=-std=c++11 -O2	-nostdlib					\
		 -Wall -Wextra -pedantic					\
		 -ffreestanding -fno-exceptions -fno-rtti
LNK=i686-elf-g++
LNKFLAGS=-O2 -ffreestanding -nostdlib
LNKLIBS=-lgcc

.PHONY: all, clean

all: $(BINARY)

$(BINARY): src/boot.s src/startup.cpp src/linker.ld makefile
	@mkdir -p bin
	@printf "[Assembler] boot.s\n"
	@mkdir -p obj
	@$(ASM) $(ASMFLAGS) src/boot.s -o obj/boot.o
	@printf "[ Compiler] startup.cpp\n"
	@$(CXX) -c src/startup.cpp -o obj/startup.o $(CXXFLAGS)
	@printf "[   Linker] dfsys.bin\n"
	@$(LNK) -T src/linker.ld -o $(BINARY) $(LNKFLAGS) obj/*.o $(LNKLIBS)

run: $(BINARY)
	@printf "[ Emulator] dfsys\n"
	@qemu-system-x86_64 -kernel $(BINARY)

clean:
	@printf "[    Clean] obj, bin\n"
	@rm -rf obj bin


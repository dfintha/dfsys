BINARY=bin/dfsys.bin
OBJECTS=obj/boot.o              \
        obj/startup.o           \
        obj/strings.o           \
        obj/termio.o            \
        obj/version.o

LNKDATA=res/linker.ld

ASM=yasm
ASMFLAGS=-f elf32

CASM=i686-elf-as

CC=i686-elf-gcc
CFLAGS=-std=c99 -O2 -nostdlib -I./include -I./res \
       -Wall -Wextra -pedantic -ffreestanding -S

CXX=i686-elf-g++
CXXFLAGS=-std=c++14 -O2	-nostdlib -I./include -I./res \
         -Wall -Wextra -pedantic -ffreestanding -fno-exceptions -fno-rtti -S

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
	@$(CC) -c $< -o $@s $(CFLAGS)
	@$(CASM) $@s -o $@

obj/%.o: src/%.cpp
	@mkdir -p obj
	@printf "[C] $<\n"
	@$(CXX) -c $< -o $@s $(CXXFLAGS)
	@$(CASM) $@s -o $@

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


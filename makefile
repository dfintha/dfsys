BINARY=bin/dfsys.bin
OBJECTS=obj/bootstrap.o         \
        obj/cpuinfo.o           \
        obj/debug.o             \
        obj/kernel.o            \
        obj/memory.o            \
        obj/stackcheck.o        \
        obj/strings.o           \
        obj/terminal.o          \
        obj/version.o           \
        obj/x86.o

LNKDATA=res/linker.ld

ASM=yasm
ASMFLAGS=-f elf32

CASM=i686-elf-as

CC=i686-elf-gcc
CFLAGS=-std=gnu99 -O2 -nostdlib -I./include -I./res                            \
       -Wall -Wextra -pedantic -ffreestanding                                  \
	   -fstack-protector -S

CXX=i686-elf-g++
CXXFLAGS=-std=c++14 -O2	-nostdlib -I./include -I./res                          \
         -Wall -Wextra -pedantic -ffreestanding -fno-exceptions -fno-rtti      \
		 -fstack-protector -S

LNK=i686-elf-g++
LNKFLAGS=-O2 -ffreestanding -nostdlib
LNKLIBS=-lgcc

CRTI=obj/crti.o
CRTB=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTE=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN=obj/crtn.o

.PHONY: all, clean

all: $(BINARY)

loc:
	@printf "[L] "
	@cat include/* src/* res/* | wc -l

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

$(BINARY): $(CRTI) $(CRTN) $(OBJECTS) $(LNKDATA)
	@mkdir -p bin
	@printf "[L] $@\n"
	@$(LNK) -T $(LNKDATA) -o $(BINARY) $(LNKFLAGS) \
		$(CRTI) $(CRTB) $(OBJECTS) $(CRTE) $(CRTN) $(LNKLIBS)

run: $(BINARY)
	@printf "[E] $(BINARY)\n"
	@qemu-system-x86_64 -kernel $(BINARY)

clean:
	@printf "[R] bin\n"
	@rm -rf bin
	@printf "[R] obj\n"
	@rm -rf obj


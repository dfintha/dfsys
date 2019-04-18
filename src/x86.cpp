#include "x86.h"
#include "memory.h"

gdtreg kgdtr;
gdtdesc kgdt[GDT_SIZE];
idtreg kidtr;
idtdesc kidt[IDT_SIZE];

extern void _asm_interrupt_0();
extern void _asm_interrupt_1();
extern void _asm_syscalls();
extern void _asm_exception_gp();
extern void _asm_exception_pf();
extern void _asm_schedule();

extern "C" gdtdesc kgdtmkdesc(uint32_t base, uint32_t lim, uint8_t access, uint8_t flags) {
    gdtdesc result;
    result.limit_0to15 = (lim & 0xFFFF);
    result.base_0to15 = (base & 0xFFFF);
    result.base_16to23 = (base & 0xFF0000) >> 16;
    result.access = access;
    result.limit_16to19 = (lim & 0x0F0000) >> 16;
    result.flags = (flags & 0x0F);
    result.base_24to31 = (base & 0xFF000000) >> 24;
    return result;
}

extern "C" void kgdtinit(void) {
    kgdt[0] = kgdtmkdesc(0x00, 0x000000, 0x00, 0x00);
    kgdt[1] = kgdtmkdesc(0x00, 0x0FFFFF, 0x9B, 0x0D);
    kgdt[2] = kgdtmkdesc(0x00, 0x0FFFFF, 0x93, 0x0D);
    kgdt[3] = kgdtmkdesc(0x00, 0x000000, 0x97, 0x0D);
    kgdt[4] = kgdtmkdesc(0x00, 0x0FFFFF, 0xFF, 0x0D);
    kgdt[5] = kgdtmkdesc(0x00, 0x0FFFFF, 0xF3, 0x0D);
    kgdt[6] = kgdtmkdesc(0x00, 0x000000, 0xF7, 0x0D);
    kgdt[7] = kgdtmkdesc(0x00, 0x000000, 0x00, 0x00);

    kgdtr.limit = GDT_SIZE * 8;
    kgdtr.base = GDT_BASE;
    kmemcopy(reinterpret_cast<char *>(kgdtr.base),
             reinterpret_cast<char *>(kgdt),
             kgdtr.limit);

    asm volatile("lgdtl (kgdtr)");
    asm volatile("movw $0x10, %ax   \n\
                  movw %ax, %ds     \n\
                  movw %ax, %es     \n\
                  movw %ax, %fs     \n\
                  movw %ax, %gs     \n\
                  ljmp $0x08, $next \n\
                  next:             \n");
}

extern "C" idtdesc kidtmkdesc(uint16_t select, uint32_t offset, uint16_t type) {
    idtdesc result;
    result.offset_0to15 = (offset & 0xFFFF);
    result.select = select;
    result.type = type;
    result.offset_16to31 = (offset & 0xFFFF0000) >> 16;
    return result;
}

extern "C" void kidtinit(void) {
    // TODO
}


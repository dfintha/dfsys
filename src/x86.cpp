#include "x86.h"
#include "memory.h"

gdtreg kgdtr;
gdtdesc kgdt[GDT_SIZE];
idtreg kidtr;
idtdesc kidt[IDT_SIZE];
tss default_tss;

external gdtdesc kgdtmkdesc(uint32_t base, uint32_t limit, uint8_t type) {
    gdtdesc result;
    result.limit_0to15 = (limit & 0xFFFF);
    result.base_0to15 = (base & 0xFFFF);
    result.base_16to23 = (base & 0xFF0000) >> 16;
    result.access = type;
    result.limit_16to19 = (limit & 0x0F0000) >> 16;
    result.flags = 0b1100;
    result.base_24to31 = (base & 0xFF000000) >> 24;
    return result;
}

#if defined(ARCH_X86)
external void kgdtinit(void) {
    kmemset(&default_tss, 0x00, sizeof(tss));
    default_tss.esp0 = 0x1FFF0;
    default_tss.ss0 = 0x18;
    default_tss.debug_flag = 0x00;
    default_tss.iopb_offset = 0x00;
    const uint32_t tssa = uint32_t(&default_tss);

    kgdt[0] = kgdtmkdesc(0x00,  0x00000000, 0x00);
    kgdt[1] = kgdtmkdesc(0x00,  0xFFFFFFFF, 0x9A);
    kgdt[2] = kgdtmkdesc(0x00,  0xFFFFFFFF, 0x92);
    kgdt[3] = kgdtmkdesc(tssa, sizeof(tss), 0x89);

    kgdtr.limit = GDT_SIZE * 4;
    kgdtr.base = GDT_BASE;
    kmemcopy(reinterpret_cast<char *>(kgdtr.base),
             reinterpret_cast<char *>(kgdt),
             kgdtr.limit);

    asm volatile("lgdtl (kgdtr)     \n\
                  movw $0x10, %ax   \n\
                  movw %ax, %ds     \n\
                  movw %ax, %es     \n\
                  movw %ax, %fs     \n\
                  movw %ax, %gs     \n\
                  ljmp $0x08, $next \n\
                  next:             \n");
}
#else
external void kgdtinit(void) {
    // TODO
}
#endif

external idtdesc kidtmkdesc(uint16_t select, uint32_t offset, uint16_t type) {
    idtdesc result;
    result.offset_0to15 = (offset & 0xFFFF);
    result.select = select;
    result.type = type;
    result.offset_16to31 = (offset & 0xFFFF0000) >> 16;
    return result;
}

external void kidtinit(void) {
    // TODO
}


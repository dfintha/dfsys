#if !defined(DFSYS_X86)
#define DFSYS_X86

#include <stdint.h>

/* x86 gdt register */
typedef struct __gdtreg {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdtreg;

/* x86 gdt descriptor */
typedef struct __gdtdesc {
    uint16_t limit_0to15;
    uint16_t base_0to15;
    uint8_t base_16to23;
    uint8_t access;
    uint8_t limit_16to19 : 4;
    uint8_t flags : 4;
    uint8_t base_24to31;
} __attribute__((packed)) gdtdesc;

/* x86 idt register */
typedef struct __idtreg {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtreg;

/* x86 idt descriptor */
typedef struct __idtdesc {
    uint16_t offset_0to15;
    uint16_t select;
    uint16_t type;
    uint16_t offset_16to31;
} __attribute__((packed)) idtdesc;

/* global x86 gdt data */
#define GDT_SIZE 0xFF
#define GDT_BASE 0x00000800
extern gdtreg kgdtr;
extern gdtdesc kgdt[GDT_SIZE];

/* global x86 idt data */
#define IDT_SIZE 0xFF
#define IDT_BASE 0x00000000
extern idtreg kidtr;
extern idtdesc kidt[IDT_SIZE];

#if defined(__cplusplus)
extern "C" {
#endif

/* returns a gdt descriptor based on the given arguments */
gdtdesc kgdtmkdesc(uint32_t base, uint32_t lim, uint8_t access, uint8_t flags);

/* initializes gdt */
void kgdtinit(void);

/* returns an idt descriptor based on the given arguments */
idtdesc kidtmkdesc(uint16_t select, uint32_t offset, uint16_t type);

/* initializes idt */
void kidtinit(void);

#if defined(__cplusplus)
}
#endif

#endif


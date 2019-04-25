#if !defined(DFSYS_X86)
#define DFSYS_X86

#include "extensions.h"
#include <stdint.h>

/* gdt access flags */
#define GDTACCESS_ACCESSED      (1 << 0)
#define GDTACCESS_RW            (1 << 1)
#define GDTACCESS_DC            (1 << 2)
#define GDTACCESS_EXECUTABLE    (1 << 3)
#define GDTACCESS_DESCTYPE      (1 << 4)
#define GDTACCESS_PRIVILIEGE    ((1 << 5) | (1 << 6))
#define GDTACCESS_PRESENT       (1 << 7)

/* gdt flags */
#define GDTFLAG_GRANULARITY     (1 << 1)
#define GDTFLAG_SIZE            (1 << 2)
#if defined(ARCH_X64)
#define GDTFLAG_L               (1 << 1)
#define GDTFLAG_SZ              (1 << 0)
#endif

/* gdt register */
typedef struct __gdtreg {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdtreg;

/* gdt descriptor */
typedef struct __gdtdesc {
    uint16_t limit_0to15;
    uint16_t base_0to15;
    uint8_t base_16to23;
    uint8_t access;
    uint8_t limit_16to19 : 4;
    uint8_t flags : 4;
    uint8_t base_24to31;
} __attribute__((packed)) gdtdesc;

/* idt register */
typedef struct __idtreg {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtreg;

/* idt descriptor */
typedef struct __idtdesc {
    uint16_t offset_0to15;
    uint16_t select;
    uint16_t type;
    uint16_t offset_16to31;
} __attribute__((packed)) idtdesc;

/* global gdt data */
#define GDT_SIZE 0xFF
#define GDT_BASE 0x00000800
extern gdtreg kgdtr;
extern gdtdesc kgdt[GDT_SIZE];

/* global idt data */
#define IDT_SIZE 0xFF
#define IDT_BASE 0x00000000
extern idtreg kidtr;
extern idtdesc kidt[IDT_SIZE];

/* returns a gdt descriptor based on the given arguments */
external gdtdesc kgdtmkdesc(uint32_t base, uint32_t lim,
                            uint8_t access, uint8_t flags);

/* initializes gdt */
external void kgdtinit(void);

/* returns an idt descriptor based on the given arguments */
external idtdesc kidtmkdesc(uint16_t select, uint32_t offset, uint16_t type);

/* initializes idt */
external void kidtinit(void);

#endif


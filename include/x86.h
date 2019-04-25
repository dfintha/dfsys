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

/* task state segment */
#if defined(ARCH_X86)
typedef struct __tss {
    uint16_t reserved1;
    uint16_t link;
    uint32_t esp0;
    uint16_t reserved2;
    uint16_t ss0;
    uint32_t esp1;
    uint16_t reserved3;
    uint16_t ss1;
    uint32_t esp2;
    uint16_t reserved4;
    uint16_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint16_t reserved5;
    uint16_t es;
    uint16_t reserved6;
    uint16_t cs;
    uint16_t reserved7;
    uint16_t ss;
    uint16_t reserved8;
    uint16_t ds;
    uint16_t reserved9;
    uint16_t fs;
    uint16_t reserved10;
    uint16_t gs;
    uint16_t reserved11;
    uint16_t ldtr;
    uint16_t iopb_offset;
    uint16_t reserved12;
} __attribute__((packed)) tss;
#else
typedef struct __tss {
    uint32_t reserved1;
    uint32_t rsp0_low;
    uint32_t rsp0_high;
    uint32_t rsp1_low;
    uint32_t rsp1_high;
    uint32_t rsp2_low;
    uint32_t rsp2_high;
    uint32_t reserved2;
    uint32_t reserved3;
    uint32_t ist1_low;
    uint32_t ist1_high;
    uint32_t ist2_low;
    uint32_t ist2_high;
    uint32_t ist3_low;
    uint32_t ist3_high;
    uint32_t ist4_low;
    uint32_t ist4_high;
    uint32_t ist5_low;
    uint32_t ist5_high;
    uint32_t ist6_low;
    uint32_t ist6_high;
    uint32_t ist7_low;
    uint32_t ist7_high;
    uint32_t reserved4;
    uint32_t reserved5;
    uint16_t iopb_offset;
    uint16_t reserved6;
} __attribute__((packed)) tss;
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


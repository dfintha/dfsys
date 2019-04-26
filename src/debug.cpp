#include "debug.h"
#include "terminal.h"

external void kdbgregdump(void) {
    uint32_t temp;
    ktermprints("\nREGISTER DUMP\n\n");

    #define dumpreg(register)                                           \
        {                                                               \
            asm volatile ("movl %%" #register ", %0" : "=r" (temp));    \
            ktermprintf("   %s: 0x%X  ", #register, temp);              \
        }

    dumpreg(eax);
    dumpreg(ebx);
    ktermprintc('\n');
    dumpreg(ecx);
    dumpreg(edx);
    ktermprintc('\n');
    dumpreg(esp);
    dumpreg(ebp);
    ktermprintc('\n');

    asm volatile ("1: lea 1b, %0;": "=a"(temp));
    ktermprintf("   eip: 0x%X  ", temp);

    dumpreg(esi);
    ktermprintc('\n');
    dumpreg(edi);

    #undef dumpreg

    asm volatile ("pushfl       \n\
                   popl %%eax   \n\
                   movl %%eax, %0" : "=r" (temp));
    ktermprintf("eflags: 0x%X\n", temp);
    ktermprintc('\n');
}

external void kdbgprint(const char *file, size_t line, const char *message) {
    ktermprintf("%s:%u: %s", file, line, message);
}

external void kdbgassert(const char *text, int criteria) {
    if (!criteria) {
        ktermprintf("assertion failed: %s\n", text);
    }
}

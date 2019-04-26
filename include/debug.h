#if !defined(DFSYS_DEBUG)
#define DFSYS_DEBUG

#include "definitions.h"

external void kdbgregdump(void);
external void kdbgprint(const char *file, size_t line, const char *message);
external void kdbgassert(const char *text, int criteria);

#define DBGASSERT(criteria)		kdbgassert(#criteria, (criteria))
#define DBGPRINT(message)		kdbgprint(__FILE__, __LINE__, (message))

#endif

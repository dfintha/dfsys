#if !defined(DFSYS_EXTENSIONS)
#define DFSYS_EXTENSIONS

#if defined(__cplusplus)
#define external extern "C"
#define internal static inline
#else
#define external
#define internal static
#endif

#if (UINT32_MAX == UINTPTR_MAX)
#define ARCH_X86
#elif (UINT64_MAX == UINTPTR_MAX)
#define ARCH_X64
#else
#error "Invalid Architecture"
#endif

#endif

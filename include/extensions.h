#if !defined(DFSYS_EXTENSIONS)
#define DFSYS_EXTENSIONS

#if defined(__cplusplus)
#define external extern "C"
#define internal static inline
#else
#define external
#define internal static
#endif

#endif


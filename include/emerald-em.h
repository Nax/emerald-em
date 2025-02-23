#ifndef EMERALD_EM_H
#define EMERALD_EM_H

#if defined(__cplusplus)
# define EMERALDEM_EXTERN_C extern "C"
#else
# define EMERALDEM_EXTERN_C
#endif

#if defined(_WIN32)
# if defined(EMERALDEM_EXPORT_DLL)
#  define EMERALDEM_EXPORT __declspec(dllexport)
# else
#  define EMERALDEM_EXPORT __declspec(dllimport)
# endif
#else
# define EMERALDEM_EXPORT
#endif

#define EMERALDEM_API EMERALDEM_EXTERN_C EMERALDEM_EXPORT

#define EMERALDEM_LANG_EN_US 0
#define EMERALDEM_LANG_FR_FR 1

typedef struct EmeraldGenerator EmeraldGenerator;

EMERALDEM_API EmeraldGenerator* EmCreate(void);
EMERALDEM_API void              EmDestroy(EmeraldGenerator* emerald);
EMERALDEM_API void              EmSetLang(EmeraldGenerator* emerald, int lang);
EMERALDEM_API void              EmSetCallbackLog(EmeraldGenerator* emerald, void (*cb)(void*, const char*), void* arg);
EMERALDEM_API void              EmSetCallbackError(EmeraldGenerator* emerald, void (*cb)(void*, const char*), void* arg);
EMERALDEM_API int               EmRun(EmeraldGenerator* emerald, const char* originalRom, const char* outputRom);

#endif

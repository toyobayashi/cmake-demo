#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
#define MAIN_EXTERN_C_START extern "C" {
#define MAIN_EXTERN_C_END }
#else
#define MAIN_EXTERN_C_START
#define MAIN_EXTERN_C_END
#endif

#ifdef _WIN32
  #ifdef MAIN_EXPORT
  #define MAIN_API __declspec(dllexport)
  #else
  #define MAIN_API __declspec(dllimport)
  #endif
#else
  #ifdef MAIN_EXPORT
  #define MAIN_API __attribute__((visibility("default")))
  #else
  #define MAIN_API
  #endif
#endif

MAIN_EXTERN_C_START

int MAIN_API add(int a, int b);

MAIN_EXTERN_C_END

#endif // !__MAIN_H__

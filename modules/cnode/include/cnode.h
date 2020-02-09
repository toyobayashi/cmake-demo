#ifndef __CNODE_H__
#define __CNODE_H__

#ifdef __cplusplus
#define CNODE_EXTERN_C_START extern "C" {
#define CNODE_EXTERN_C_END }
#else
#define CNODE_EXTERN_C_START
#define CNODE_EXTERN_C_END
#endif

#ifdef _WIN32
  #ifdef CNODE_DLL_EXPORT
  #define CNODE_API __declspec(dllexport)
  #else
  #define CNODE_API __declspec(dllimport)
  #endif
#else
  #ifdef CNODE_DLL_EXPORT
  #define CNODE_API __attribute__((visibility("default")))
  #else
  #define CNODE_API
  #endif
#endif

#include <stddef.h>

CNODE_EXTERN_C_START

int CNODE_API cnode_fs_readdir(const char*, char**, size_t*);
int CNODE_API cnode_fs_read_file_as_string(const char*, char*, size_t*);

CNODE_EXTERN_C_END

#endif // !__CNODE_H__

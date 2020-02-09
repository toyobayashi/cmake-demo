#ifdef _WIN32
#include <Windows.h>
#include "../include/main.h"
typedef void (*Fn)(int, int);
void self_call() {
  HMODULE addon = LoadLibraryA("addon.dll");
  if (addon) {
    Fn call_main_export = (Fn)GetProcAddress(addon, "call_main_export");
    if (call_main_export) {
      call_main_export(3, 4);
    }
  }
}

int add(int a, int b) {
  return a + b;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "cnode.h"

static int test_read_dir() {
  int code;
  size_t entry_count;
  size_t i;
  char** res;
  size_t size;

  const char path[] = ".";
  entry_count = 0;
  code = cnode_fs_readdir(path, NULL, &entry_count);
  if (code) {
    return code;
  }
  if (entry_count == 0) {
    printf("size: 0\n");
    return 2;
  }
  res = (char**)malloc(entry_count * sizeof(char*));
  if (!res) {
    return 1;
  }
  for (i = 0; i < entry_count; i++) {
    *(res + i) = (char*)malloc(260 * sizeof(char));
    if (!(*(res + i))) {
      return 1;
    }
    memset(*(res + i), 0, 260);
  }
  size = entry_count;
  code = cnode_fs_readdir(path, res, &size);
  if (code) {
    for (i = 0; i < entry_count; i++) {
      free(*(res + i));
    }
    free(res);
    return code;
  }
  printf("size: %ld\n", size);
  for (i = 0; i < size; i++) {
    printf("%s\n", *(res + i));
  }
  for (i = 0; i < entry_count; i++) {
    free(*(res + i));
  }
  free(res);
  return 0;
}

static int test_read_file_as_string() {
  int code;
  size_t length;
#ifdef _WIN32
  const char path[] = "./build.bat";
#else
  const char path[] = "./build.sh";
#endif
  char* res;
  size_t in_out_count;

  code = cnode_fs_read_file_as_string(path, NULL, &length);
  if (code) {
    return code;
  }
  res = (char*)malloc((length + 1) * sizeof(char));
  if (!res) {
    return 1;
  }
  in_out_count = length;
  code = cnode_fs_read_file_as_string(path, res, &in_out_count);
  if (code) {
    free(res);
    return code;
  }

  printf("size: %ld\n", length);
  printf("size: %ld\n", in_out_count);
  printf("%s\n", res);

  free(res);
  return 0;
}



int main(int argc, char* argv[]) {
  printf("Start.\n\n");
#ifdef _WIN32
  // system("chcp 65001>nul");
#endif // _WIN32
  int code;
  code = test_read_dir();
  if (code) {
    return code;
  }
  code = test_read_file_as_string();
  if (code) {
    return code;
  }

#ifdef _WIN32
  self_call();
#endif // _WIN32
  return 0;
}

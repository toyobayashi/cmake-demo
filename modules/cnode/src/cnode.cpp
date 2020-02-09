#include "cnode.h"
#include "fs.hpp"
#include <vector> // std::vector
#include <string> // std::string
#include <cstddef> // size_t
#include <cstring> // strcpy

// 中文
int cnode_fs_readdir(const char* path, char** result, size_t* size) {
  if (!result) {
    try {
      auto unuse = cnode::fs::readdir(path, size);
      return 0;
    } catch (const std::exception&) {
      return 1;
    }
  }

  std::vector<std::string> res;
  try {
    res = cnode::fs::readdir(path);
  } catch (const std::exception&) {
    return -1;
  }

  size_t buf_size = res.size();
  size_t real_size = buf_size;
  if (size) {
    size_t limit = *size;
    real_size = limit > buf_size ? buf_size : limit;
  }
  size_t i = 0;
  for (; i < real_size; i++) {
    strcpy(result[i], res[i].c_str());
  }
  if (size) {
    *size = real_size;
  }

  return 0;
}

int cnode_fs_read_file_as_string(const char* path, char* result, size_t* size) {
  if (!result) {
    try {
      auto unuse = cnode::fs::read_file_as_string(path, size);
      return 0;
    } catch (const std::exception&) {
      return 1;
    }
  }

  std::string res;
  try {
    res = cnode::fs::read_file_as_string(path);
  } catch (const std::exception&) {
    return 1;
  }

  size_t buf_size = res.length();
  size_t real_size = buf_size;
  if (size) {
    size_t limit = *size;
    real_size = limit > buf_size ? buf_size : limit;
  }
  size_t i = 0;
  for (; i < real_size; i++) {
     result[i] = res[i];
  }
  result[i] = '\0';
  if (size) {
    *size = real_size;
  }
  return 0;
}

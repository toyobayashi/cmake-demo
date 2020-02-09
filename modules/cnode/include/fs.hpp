#ifndef __CNODE_FS_HPP__
#define __CNODE_FS_HPP__

#include "charset.hpp"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cstddef>

namespace cnode {
  namespace fs {
    std::vector<std::string> readdir(const std::string& path, size_t* entry_size = nullptr) {
#ifdef _WIN32
      std::wstring wpath = a2w(path);
      std::filesystem::directory_iterator dit(wpath);
#else
      std::filesystem::directory_iterator dit(path);
#endif
      if (entry_size) {
        *entry_size = 0;
        for (auto& p : dit) {
          *entry_size = *entry_size + 1;
        }
        return {};
      }

      std::vector<std::string> res;
      for (auto& p : dit) {
        std::filesystem::path filename = p.path().filename();
#ifdef _WIN32
        res.push_back(w2a(filename.wstring()));
#else
        res.push_back(filename.string());
#endif
      }
      return res;
    }

    std::vector<unsigned char> read_file_as_vector(const std::string& path, size_t *file_size = nullptr) {
#ifdef _WIN32
      std::wstring wpath = a2w(path);
      std::ifstream f(wpath, std::ios::binary | std::ios::in | std::ios::ate);
#else
      std::ifstream f(path, std::ios::binary | std::ios::in | std::ios::ate);
#endif
      std::streampos size = f.tellg();
      if (file_size) {
        *file_size = static_cast<size_t>(size);
        return {};
      }
      unsigned char* buf = new unsigned char[static_cast<unsigned int>(size)];
      f.seekg(std::ios::beg);
      f.read(reinterpret_cast<char*>(buf), size);
      std::vector<unsigned char> res(buf, buf + size / sizeof(unsigned char));
      delete[] buf;
      f.close();
      return res;
    }

    std::string read_file_as_string(const std::string& path, size_t* file_size = nullptr) {
#ifdef _WIN32
      std::wstring wpath = a2w(path);
      std::ifstream f(wpath, std::ios::binary | std::ios::in | std::ios::ate);
#else
      std::ifstream f(path, std::ios::binary | std::ios::in | std::ios::ate);
#endif
      std::streampos size = f.tellg();
      if (file_size) {
        *file_size = static_cast<size_t>(size);
        return "";
      }
      std::streampos zero = 1;
      char* buf = new char[static_cast<unsigned int>(size + zero)];
      f.seekg(std::ios::beg);
      f.read(buf, size);
      buf[static_cast<int>(size)] = '\0';
      std::string res(buf);
      delete[] buf;
      f.close();
      return res;
    }
  }
}

#endif

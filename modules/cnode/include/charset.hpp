#ifndef __CNODE_CHARSET_HPP__
#define __CNODE_CHARSET_HPP__

#include <clocale>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <string>

void set_locale_utf8() {
  std::string target_locale = "en_US.utf8";
  const char* c_locale = std::setlocale(LC_CTYPE, nullptr);
  std::string locale(c_locale ? c_locale : "");

  if (locale != target_locale) {
    std::setlocale(LC_CTYPE, target_locale.c_str());
  }
}

std::wstring a2w(const std::string& str) {
  /*int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
  if (len == -1) {
    throw std::exception("Convert failed.");
  }
  wchar_t* buf = new wchar_t[len];
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buf, len);
  std::wstring res(buf);
  delete[] buf;
  return res;*/
  set_locale_utf8();
  size_t len = std::mbstowcs(nullptr, str.c_str(), 0);
  wchar_t* buf = new wchar_t[len + 1];
  std::mbstowcs(buf, str.c_str(), len + 1);
  std::wstring res(buf);
  delete[] buf;
  return res;
}
std::string w2a(const std::wstring& wstr) {
  /*int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, NULL, NULL);
  if (len == -1) {
    throw std::exception("Convert failed.");
  }
  char* buf = new char[len];
  WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, buf, len, NULL, NULL);
  std::string res(buf);
  delete[] buf;
  return res;*/
  set_locale_utf8();
  size_t len = std::wcstombs(nullptr, wstr.c_str(), 0);
  char* buf = new char[len + 1];
  std::wcstombs(buf, wstr.c_str(), len + 1);
  std::string res(buf);
  delete[] buf;
  return res;
}

#endif // !__CNODE_CHARSET_HPP__

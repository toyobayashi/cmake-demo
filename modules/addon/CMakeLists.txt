cmake_minimum_required(VERSION 3.15)

project(addon)

add_library(addon SHARED
  src/addon.c
)

if(WIN32 AND MSVC)
  set_target_properties(addon PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  target_compile_options(addon PRIVATE /utf-8)
  target_compile_definitions(addon PRIVATE
    _CRT_SECURE_NO_WARNINGS
    UNICODE
    _UNICODE
  )
  message(${CMAKE_CURRENT_SOURCE_DIR}/../../build/win32/Release/main.lib)
  target_link_libraries(addon ${CMAKE_CURRENT_SOURCE_DIR}/../../build/win32/Release/main.lib)
  target_link_options(addon PRIVATE /ignore:4199 /DELAYLOAD:main.exe)
endif()

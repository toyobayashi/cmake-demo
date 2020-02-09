cmake_minimum_required(VERSION 3.15)

project(main)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(main
  src/main.c
)

if(WIN32 AND MSVC)
  set_directory_properties(PROPERTIES VS_STARTUP_PROJECT main)
  set_target_properties(main PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  target_compile_options(main PRIVATE /utf-8)
  target_compile_definitions(main PRIVATE
    _CRT_SECURE_NO_WARNINGS
    UNICODE
    _UNICODE
    MAIN_EXPORT
  )

  target_link_options(main PRIVATE /ignore:4199 /DELAYLOAD:cnode.dll)
endif()

add_subdirectory(modules/cnode)

target_link_libraries(main PRIVATE cnode)

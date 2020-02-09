cmake_minimum_required(VERSION 3.15)

project(cnode)

set(CMAKE_CXX_STANDARD 17)

add_library(cnode SHARED
  src/cnode.cpp
)

if(WIN32 AND MSVC)
  set_target_properties(cnode PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  target_compile_options(cnode PRIVATE /utf-8)
  target_compile_definitions(cnode PRIVATE
    _CRT_SECURE_NO_WARNINGS
    UNICODE
    _UNICODE
  )
else()
  # set(CMAKE_CXX_FLAGS "-lstdc++fs ${CMAKE_CXX_FLAGS}")
  target_link_libraries(cnode stdc++fs)
  target_compile_options(cnode PRIVATE -lstdc++fs)
endif()

target_compile_definitions(cnode PRIVATE
  CNODE_DLL_EXPORT
)

target_include_directories(cnode
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)

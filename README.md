# cmake 示例项目

## 环境要求

Windows:

* cmake >= 3.15

* Visual Studio 2019 （安装 C++ 工作负载）

WSL:

* cmake >= 3.15

* gcc-8 & g++-8 （C++ 17 filesystem）

* gdb （VSCode 调试用）

* make

## 要点

* C 代码和 C++ 代码互调

* 编写动态链接库

* Windows 下延迟加载 DLL

* Windows 下纯动态加载的 DLL 再加载可执行文件暴露的函数时，可执行文件可以重命名（node-gyp 中的处理方法）

# KiroEngine

KiroEngine is a modern 3D game engine developed in C++23, designed for cross-platform support. It features:

- Graphics APIs: Vulkan (primary), DirectX 11/12 support planned
- Windowing: Win32 API on Windows (Linux support in future)
- GUI: ImGui integration for tools and debugging
- Modular, extensible architecture
- Build system: CMake (flexible cross-platform build configuration)
- Focus on best practices and maintainability

## Getting Started

### Prerequisites
- Visual Studio 2022 or later
- CMake 3.31+
- Vulkan SDK installed (for Windows)
- Git

### Building

```bash
git clone https://github.com/tanapatnamsomboon/KiroEngine.git
cd KirEngine
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release

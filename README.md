# PricePulse

PricePulse is a product and price monitoring tool built in C++20 using Qt 6.8.3

---

## Required Tools for Build

1. **Visual Studio 2022** (Community/Professional/Enterprise) with:
   - Desktop development with C++
   - C++ CMake tools for Windows
   - Windows 10 SDK

2. **Qt 6.8.3 MSVC 2022 64-bit**
   - Required modules: Core, Gui, Widgets, Network, Sql
   - Optional: WebEngineWidgets (for future extensions)

3. **CMake 3.24+**

---

## Build Steps (Windows)

1. Clone the repository:

`git clone https://github.com/ALINCOP/PricePulse.git`
`cd PricePulse`

2. Create and enter the build folder:
`mkdir build
cd build`

3. Configure the project with CMake:
`cmake .. -G "Visual Studio 17 2022" -A x64 -DQt6_DIR="C:\Qt\6.8.3\msvc2022_64\lib\cmake\Qt6"`

4. Build the project:
`cmake --build . --config Release`

Executable will be generated in: build/bin/PricePulse.exe

cmake_minimum_required(VERSION 3.24)
project(PricePulse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_PREFIX_PATH "C:/Qt/6.7.3/msvc2022_64" CACHE PATH "Qt installation root")

# QT6 automatic build functions
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Linux in the future
if(WIN32)
    message(STATUS "Configuring for Windows (MSVC)")
elseif(UNIX)
    message(STATUS "Configuring for Linux/Unix")
endif()

find_package(Qt6 6.7 COMPONENTS Core Gui Widgets Network Sql WebEngineWidgets REQUIRED)

set(SOURCES
    src/main.cpp
    src/ui/MainWindow.cpp
    src/ui/AddProductDialog.cpp
    src/core/TaskManager.cpp
    src/core/DatabaseManager.cpp
    src/core/PriceScraper.cpp
)

set(HEADERS
    src/ui/MainWindow.h
    src/ui/AddProductDialog.h
    src/core/TaskManager.h
    src/core/DatabaseManager.h
    src/core/Product.h
    src/core/PriceScraper.h
)

set(UIS
    src/ui/MainWindow.ui
    src/ui/AddProductDialog.ui
)

# Create exe
qt_add_executable(PricePulse
    ${SOURCES}
    ${UIS}
)

target_link_libraries(PricePulse PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
    Qt6::WebEngineWidgets
)

# Include source directories
target_include_directories(PricePulse PRIVATE 
    src
    src/core
    src/ui
    $<TARGET_PROPERTY:PricePulse,AUTOUIC_INCLUDE_DIRECTORIES>
)


set_target_properties(PricePulse PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# --- Deploying QT Dlls ---
if(WIN32)
    add_custom_command(TARGET PricePulse POST_BUILD
        COMMAND "${Qt6_DIR}/../../../bin/windeployqt.exe" $<TARGET_FILE:PricePulse>
        COMMENT "Deploying Qt DLLs for Windows"
    )
endif()

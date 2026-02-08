cmake_minimum_required(VERSION 3.15)
project(AutoWorkshopMenu VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Для Windows
if(WIN32)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

# Все исходные файлы
set(SOURCES
    src/Car.cpp
    src/autoworkshop_lib.cpp
    interactive_menu.cpp
)

# Все заголовочные файлы
set(HEADERS
    include/Header1.h
    include/autoworkshop_lib.hpp
)

# Создаем исполняемый файл меню
add_executable(AutoMenu ${SOURCES} ${HEADERS})

# Директории с заголовками
target_include_directories(AutoMenu PRIVATE include)
target_include_directories(AutoMenu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Устанавливаем выходную директорию
set_target_properties(AutoMenu PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
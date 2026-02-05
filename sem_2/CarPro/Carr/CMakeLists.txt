project(Carr)

# Добавляем заголовки
set(HEADERS
    CarLibrary.hpp
    AutoMaster.h
    Magnitola.h
    # ... другие заголовки
)

# Добавляем исходники
set(SOURCES
    Carr.cpp
    AutoMaster.cpp
    Magnitola.cpp
    # ... другие исходники
)

# Создаем библиотеку
add_library(Carr ${SOURCES} ${HEADERS})

# Указываем, где искать заголовки этой библиотеки
target_include_directories(Carr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Если нужны настройки компиляции
target_compile_features(Carr PRIVATE cxx_std_17)
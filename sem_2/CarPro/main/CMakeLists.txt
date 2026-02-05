# Основной исполняемый проект
project(main)

# Добавляем заголовки
set(HEADERS
    Header1.h
)

# Добавляем исходники
set(SOURCES
    main.cpp
    Car.cpp
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключаем библиотеку Carr
target_link_libraries(${PROJECT_NAME} PRIVATE Carr)

# Добавляем пути к заголовкам:
# 1. Текущая папка (для Header1.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 2. Если нужно подключить заголовки из Carr
# (обычно не нужно, т.к. Carr уже объявил PUBLIC include директории)

# Настройки компиляции
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
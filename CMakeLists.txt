cmake_minimum_required(VERSION 3.30)
project(Israel_Lara_Caso_Integrador_4)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 14)

# Incluir directorios para cabeceras
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/libs)

# Declarar los archivos fuente
add_executable(Israel_Lara_Caso_Integrador_4
        src/funciones.cpp
        src/funciones.h
        src/variant.cpp
        src/variant.h
        main.cpp
        libs/json11.cpp)

cmake_minimum_required(VERSION 3.30)
project(Israel_Lara_Caso_Integrador_4)

set(CMAKE_CXX_STANDARD 14)

include_directories(src json)

add_executable(Israel_Lara_Caso_Integrador_4
    src/funciones.cpp
    src/funciones.h
    src/variant.cpp
    src/variant.h
    main.cpp)
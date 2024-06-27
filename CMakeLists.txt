cmake_minimum_required(VERSION 3.28)
project(plantamiz C)
link_libraries(alleg)
set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(plantamiz main.c evaluation.c evaluation.h
        plantamiz.h
        plateau.c
        plateau.h
        affichage.c
        affichage.h
        jeux.c)

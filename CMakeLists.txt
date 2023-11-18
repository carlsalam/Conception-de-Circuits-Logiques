cmake_minimum_required(VERSION 3.26)
project(TP2_Gr02_EquipeC)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TP2_Gr02_EquipeC
        .gitattributes
        .gitignore
        circuit_logique.c
        t_circuit.h
        t_entree.h
        t_file_porte.c
        t_file_porte.h
        t_pin_entree.c
        t_pin_entree.h
        t_pin_sortie.c
        t_pin_sortie.h
        t_porte.h
        t_sortie.h
        main.c
        t_entree.c
        t_sortie.c
        t_porte.c
        t_circuit.c)

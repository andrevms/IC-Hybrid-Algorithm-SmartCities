cmake_minimum_required(VERSION 3.10)

# set the project name
project(IC-HYBRID-ALGORITHM-SMARTCITIES VERSION 1.0)

# add the executable
add_executable(
    IC-HYBRID-ALGORITHM-SMARTCITIES
   
    libs/entity/pathTS.h libs/entity/pathTS.c
    libs/entity/matrizAdjacente.h libs/entity/matrizAdjacente.c
    libs/entity/passageiros.h libs/entity/passageiros.c
    libs/entity/carro.h libs/entity/carro.c
    libs/entity/container.h libs/entity/container.c
    
    main.c
)

target_include_directories(
    IC-HYBRID-ALGORITHM-SMARTCITIES
    PRIVATE libs/entity
    )
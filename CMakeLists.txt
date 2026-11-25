cmake_minimum_required(VERSION 3.12)
project(DNA_Genome_Reconstruction LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(dna_assembler
    main.cpp
    dna_utils.cpp
    read_parser.cpp
    overlap.cpp
    overlap_graph.cpp
    assembler.cpp
    output.cpp
    stats.cpp
)

cmake_minimum_required(VERSION 3.18)
project(oh_shell)

set(CMAKE_CXX_STANDARD 14)

# set build output file dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

# set source file dir
include_directories(src)

# build main program
file(
    GLOB oh_shell
    "src/*.cpp"
    "src/core/*.cpp"
)
add_executable(
    oh_shell ${oh_shell}
)

# set test sub dir
add_subdirectory("test")

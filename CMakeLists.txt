project(cph C)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE
    src/cph.c
    src/argparse.c
    src/cph_clipboard_handler.c
    src/cph_input_handler.c
    src/cph_key.c)

set(HEADERS
    src/argparse.h
    src/cph_clipboard_handler.h
    src/cph_input_handler.h
    src/cph_key.h)

#There are lots of scripts with cmake for finding external libraries.
#see /usr/local/share/cmake-2.6/Modules/Find*.cmake for more examples
find_package(Libgcrypt REQUIRED)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(cph ${SOURCE} ${HEADERS})
# Link the target to the GTK+ libraries
target_link_libraries(cph ${GTK3_LIBRARIES} ${LIBGCRYPT_LIBS})
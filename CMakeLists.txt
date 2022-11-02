cmake_minimum_required(VERSION 3.5)

project(seqseq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS -stdlib=libc++)

add_subdirectory(src)
add_subdirectory(lib)

#install(TARGETS seqseq
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    RUNTIME DESTINATION bin
#)

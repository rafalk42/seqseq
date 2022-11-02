#target_include_directories(TCLAP PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB HEADER_FILES tclap/*.h)

add_library(TCLAP INTERFACE ${HEADER_FILES})
target_include_directories(TCLAP INTERFACE .)
#add_subdirectory(tclap)

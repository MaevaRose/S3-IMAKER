include_directories(.)
file(GLOB_RECURSE SRC_FILES *.cpp *.h)
add_library(imgui ${SRC_FILES})

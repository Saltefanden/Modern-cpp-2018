#################### Import the 'io_tools' library here ########################

# SUUUUPER IMPORTANT AS FIND LIBRARY DOES ONLY INCLUDE PER STANDARD .dll.a.a.lib. 
# ADD .so TO THAT LIST
set(CMAKE_FIND_LIBRARY_SUFFIXES .so ${CMAKE_FIND_LIBRARY_SUFFIXES})

find_library(io_tools 
             NAMES io_tools
             PATHS ${EXECUTABLE_OUTPUT_PATH})


#################### Create a library 'image' below this line ##################
include_directories(${PROJECT_SOURCE_DIR}/src/igg_image/)
add_library(image image.cpp)

target_link_libraries(image ${io_tools})

# What explains the shared library issues with windows:
# https://ibob.bg/blog/2018/12/16/windows-rpath/
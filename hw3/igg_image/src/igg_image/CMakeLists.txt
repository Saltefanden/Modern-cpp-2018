add_subdirectory(io_strategies)

# TODO: create image library from image.cpp.
include_directories(${PROJECT_SOURCE_DIR}/src/igg_image/
                    ${PROJECT_SOURCE_DIR}/src/igg_image/io_strategies/)

add_library(image image.cpp)

# TODO: link image library to any other libraries if needed.
target_link_libraries(image strategies)

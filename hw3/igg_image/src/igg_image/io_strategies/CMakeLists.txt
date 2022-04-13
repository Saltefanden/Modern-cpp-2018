add_library(strategies
            # TODO: Add other files here when needed.
            dummy_strategy.cpp
            png_strategy.cpp
            ppm_strategy.cpp)
# TODO: link strategies against needed libraries.

find_package(PNG REQUIRED)

# message(!!!!!!!!!!!  ${PNG_LIBRARY})
# sudo apt install build-essential libpng++-dev

target_link_libraries(strategies ${PNG_LIBRARY})

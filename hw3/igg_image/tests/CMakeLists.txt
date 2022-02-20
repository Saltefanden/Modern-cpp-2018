include(FetchContent)

FetchContent_Declare(
    googletest
    # Specify the commit you depend on and update it regularly.
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(googletest/googletest/include)
include_directories(${PROJECT_SOURCE_DIR}/src/igg_image/
                    ${PROJECT_SOURCE_DIR}/src/igg_image/io_strategies/)


include(CTest) # Include testing cmake package.
set(TEST_BINARY ${PROJECT_NAME}_test)
add_executable(
 ${TEST_BINARY}
 test_init.cpp
#  # test_resize.cpp
#  # test_dummy_strategy.cpp
#  # test_histogram.cpp
#  # test_from_ppm.cpp
#  # test_from_png.cpp
)


target_link_libraries(${TEST_BINARY}
  image
  strategies
  gtest gtest_main
)


add_test(
  NAME ${TEST_BINARY}
  COMMAND ${EXECUTABLE_OUTPUT_PATH}/${TEST_BINARY}
  WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

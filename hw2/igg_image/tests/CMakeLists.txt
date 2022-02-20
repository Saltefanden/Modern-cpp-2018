# If you are not on Linux, you will need to download the source of the
# googletest framework manually and provide the folder to which you have
# - downloaded it by copying this link into your browser:
#   https://github.com/google/googletest/archive/release-1.8.0.zip
# - unpack it into some <FOLDER>
# - use this <FOLDER> instead of /usr/src/gtest in the line below.
# add_subdirectory(/usr/src/gtest
#                  ${PROJECT_BINARY_DIR}/gtest)

include(FetchContent)
FetchContent_Declare(
    googletest
    # Specify the commit you depend on and update it regularly.
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(googletest/googletest/include)
include_directories(${PROJECT_SOURCE_DIR}/src/igg_image/)


include(CTest) # Include testing cmake package.
set(TEST_BINARY ${PROJECT_NAME}_test)

##################### Create your tests below this line ########################

add_executable(${TEST_BINARY} test_image.cpp)

target_link_libraries(${TEST_BINARY}
    image
    ${io_tools}
    gtest gtest_main
)

add_test(
    NAME test_image
    COMMAND ${EXECUTABLE_OUTPUT_PATH}/${TEST_BINARY}
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH} # Important for the search path for image data in the tests. 
)

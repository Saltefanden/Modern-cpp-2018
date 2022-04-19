
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include_directories(
    googletest/googletest/include
)

include(CTest) # Include testing cmake package.

set(TEST_BINARY ${PROJECT_NAME}_test)
##################### Create your tests below this line ########################
foreach(testfile
        casting
        modoperations)
    
    set(TEST_BINARY ${testfile}_test)

    add_executable(${TEST_BINARY} 
        test_${testfile}.cpp
    )
    
    target_link_libraries(${TEST_BINARY}
        digit_counting
        gtest gtest_main
    )
    
    add_test(
        NAME test_${testfile}
        COMMAND ${EXECUTABLE_OUTPUT_PATH}/${TEST_BINARY}
        WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH} # Important for the search path for image data in the tests. 
    )

endforeach()



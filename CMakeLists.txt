cmake_minimum_required(VERSION 3.9)
project(IEX_DEEP_HISTORICAL_DATA_PARSER VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Main file
add_executable(iex_deep_parser src/main.cpp)

# Setting up tests
# Google test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#enable_testing()
include(CTest)
include(GoogleTest)

add_executable(messagetype_test tests/messagetype_test.cc)
target_link_libraries(messagetype_test gtest_main)
gtest_discover_tests(messagetype_test)

add_executable(datatype_test tests/datatype_test.cc)
target_link_libraries(datatype_test gtest_main)
gtest_discover_tests(datatype_test)

add_executable(messages_test tests/messages_test.cc)
target_link_libraries(messages_test gtest_main)
gtest_discover_tests(messages_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

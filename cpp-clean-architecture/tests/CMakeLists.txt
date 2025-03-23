project(CleanArchitectureTests)

enable_testing()

include(GoogleTest)
find_package(GTest CONFIG REQUIRED)

add_executable(CleanArchitectureTests
        ${CMAKE_CURRENT_SOURCE_DIR}/domain_tests/user_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/infrastructure_tests/in_memory_user_repository_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/usecases_tests/user_service_tests.cpp
)

target_link_libraries(CleanArchitectureTests
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        Core
        Infrastructure
)

target_include_directories(console PRIVATE
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src
#        ${CMAKE_BINARY_DIR}/cpp-clean-architecture/src/core/include
#        ${CMAKE_BINARY_DIR}/cpp-clean-architecture/src/infrastructure/include
)

add_test(NAME UserTests COMMAND CleanArchitectureTests)
project(Console)

add_executable(console main.cpp)

target_link_libraries(console PRIVATE Core Infrastructure)

target_include_directories(console PRIVATE
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src
#        ${CMAKE_BINARY_DIR}/cpp-clean-architecture/src/core/include
#        ${CMAKE_BINARY_DIR}/cpp-clean-architecture/src/infrastructure/include
)
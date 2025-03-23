project(Infrastructure)

include(GenerateExportHeader)

add_library(${PROJECT_NAME} SHARED
    persistence/in_memory_user_repository.hpp
    persistence/in_memory_user_repository.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/persistence
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src/core
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src/core/domain/entities
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src/core/domain/repositories
        ${CMAKE_BINARY_DIR}/cpp-clean-architecture/src/core/include
        ${CMAKE_CURRENT_BINARY_DIR}/include
)

generate_export_header(${PROJECT_NAME}
        BASE_NAME Infrastructure
        EXPORT_MACRO_NAME INFRASTRUCTURE_API
        EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}_export.h
)


if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    target_compile_options(${PROJECT_NAME} PUBLIC /wd4251 /wd4275)
else()
    target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -Wpedantic)
endif()


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Core
)

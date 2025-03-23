project(Core)

include(GenerateExportHeader)

add_library(${PROJECT_NAME} SHARED)

add_subdirectory(domain/entities)
add_subdirectory(domain/repositories)
add_subdirectory(usecases)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE CORE_EXPORTS)


target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src/core/domain/entities
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src/core/domain/repositories
        ${CMAKE_CURRENT_SOURCE_DIR}/usecases
        ${CMAKE_CURRENT_BINARY_DIR}/include
)

generate_export_header(${PROJECT_NAME}
        BASE_NAME Core
        EXPORT_MACRO_NAME CORE_API
        EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/core_export.h
)


message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_SOURCE: ${CMAKE_SOURCE_DIR}")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    target_compile_options(${PROJECT_NAME} PUBLIC /wd4251)
else()
    target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -Wpedantic)
endif()


install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/domain
        DESTINATION include/core
        FILES_MATCHING PATTERN "*.hpp")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/usecases
        DESTINATION include/core
        FILES_MATCHING PATTERN "*.hpp")
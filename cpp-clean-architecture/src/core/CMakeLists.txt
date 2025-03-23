project(Core)

add_library(${PROJECT_NAME} SHARED)

add_subdirectory(domain/entities)
add_subdirectory(domain/repositories)
add_subdirectory(usecases)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE CORE_EXPORTS)


target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src # Use this root path instead
)


include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
        BASE_NAME Core
        EXPORT_MACRO_NAME CORE_API
        EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}_export.h
)
set(INCLUDE_INSTALL_DIR include)
install(FILES
        ${PROJECT_BINARY_DIR}/core_export.h
        DESTINATION ${INCLUDE_INSTALL_DIR}
)

message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_SOURCE: ${CMAKE_SOURCE_DIR}")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    target_compile_options(${PROJECT_NAME} PUBLIC /wd4251)
else()
    target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -Wpedantic)
endif()


export(TARGETS ${PROJECT_NAME} FILE "${CMAKE_CURRENT_BINARY_DIR}/ProjektATargets.cmake")
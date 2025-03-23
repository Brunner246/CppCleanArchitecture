project(Adapters)

include(GenerateExportHeader)

find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME}
        PUBLIC
        user_adapter.hpp
        PRIVATE
        user_adapter.cpp
)

message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PRIVATE
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src # Use this root path instead
)

generate_export_header(${PROJECT_NAME}
        BASE_NAME Adapters
        EXPORT_MACRO_NAME ADAPTERS_API
        EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}_export.h
)

set(INCLUDE_INSTALL_DIR include)
install(FILES
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_export.h
        DESTINATION ${INCLUDE_INSTALL_DIR}
)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /utf-8)
    target_compile_options(${PROJECT_NAME} PUBLIC /wd4251 /wd4275)
else ()
    target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -Wpedantic)
endif ()

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Core
        Infrastructure
        Crow::Crow
        nlohmann_json::nlohmann_json
)

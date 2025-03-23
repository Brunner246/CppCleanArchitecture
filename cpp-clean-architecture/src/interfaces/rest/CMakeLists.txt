project(RestApi)

find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
)

add_subdirectory(controllers)
add_subdirectory(dto)
add_subdirectory(server)

message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/cpp-clean-architecture/src # Use this root path instead
)


if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
    target_compile_options(${PROJECT_NAME} PUBLIC /wd4251 /wd4275)
else()
    target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
        Core
        Infrastructure
        Adapters
        Crow::Crow
        nlohmann_json::nlohmann_json
)

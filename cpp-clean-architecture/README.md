# cpp-clean-architecture

This project demonstrates a clean architecture implementation in modern C++ (C++23) using CMake. The focus is on maintaining a clear separation of concerns, making the codebase easier to manage, test, and extend.

## Project Structure

- **CMakeLists.txt**: Top-level CMake configuration file that defines the project and includes subdirectories for core, infrastructure, and interfaces.
- **src/**: Contains the source code for the application.
  - **core/**: Contains the core business logic.
    - **domain/**: Defines the entities and repositories.
      - **entities/**: Contains the `User` class representing a user entity.
      - **repositories/**: Declares the `UserRepository` interface for user data access.
    - **usecases/**: Implements the `UserService` class for business logic related to users.
  - **infrastructure/**: Contains the implementation details for data persistence.
    - **persistence/**: Implements the `InMemoryUserRepository` for storing and retrieving users in memory.
  - **interfaces/**: Contains the entry point of the application.
    - **console/**: The main application logic that interacts with the user service.
- **tests/**: Contains unit tests for the application components.
  - **domain_tests/**: Tests for the `User` class.
  - **infrastructure_tests/**: Tests for the `InMemoryUserRepository`.
  - **usecases_tests/**: Tests for the `UserService`.
- **vcpkg.json**: Specifies the dependencies for the project, managed using vcpkg.

## Building the Project

To build the project, follow these steps:

1. Ensure you have CMake installed on your system.
2. Clone the repository:
   ```
   git clone <repository-url>
   cd cpp-clean-architecture
   ```
3. Create a build directory:
   ```
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   cmake --build .
   ```

## Running the Application

After building the project, you can run the application by executing the compiled binary located in the `build` directory.

## Running Tests

To run the tests, you can use the following command in the build directory:

```
ctest
```

This will execute all the unit tests defined in the `tests` directory.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.
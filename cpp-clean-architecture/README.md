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
    - **interfaces/**: Contains the entry points of the application.
        - **console/**: The console application interface that interacts with the user service.
        - **rest/**: The REST API interface for HTTP-based interactions.
            - **controllers/**: REST controllers that handle HTTP requests and responses.
            - **dto/**: Data Transfer Objects for API request/response serialization.
            - **server/**: Server implementation and configuration.
    - **adapters/**: Contains adapters for mapping between different layers of the application.
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
`./build/src/interfaces/console/ConsoleApp`

### REST API Interface
Run the REST API server to interact via HTTP requests:
`./build/src/interfaces/rest/RestApiServer`

The REST API exposes endpoints for user management:
- `GET /api/users`: Get all users
- `GET /api/users/{id}`: Get user by ID
- `POST /api/users`: Create a new user
- `PUT /api/users/{id}`: Update an existing user
- `DELETE /api/users/{id}`: Delete a user

## Running Tests

To run the tests, you can use the following command in the build directory:

## Running Tests

To run the tests, you can use the following command in the build directory:

```
ctest
```

This will execute all the unit tests defined in the `tests` directory.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.

```text
cpp-clean-architecture/
├── src/
│   ├── core/                       # Core domain layer
│   │   ├── domain/                 # Domain models and interfaces
│   │   │   ├── entities/           # Business entities
│   │   │   └── repositories/       # Repository interfaces
│   │   └── usecases/               # Application business rules
│   ├── infrastructure/             # External frameworks and tools
│   │   └── persistence/            # Data storage implementations
│   ├── interfaces/                 # Entry points to the system
│   │   ├── console/                # Command-line interface
│   │   └── rest/                   # REST API interface
│   │       ├── controllers/        # HTTP request handlers
│   │       ├── dto/                # Data transfer objects
│   │       └── server/             # Server configuration
│   └── adapters/                   # Layer translation adapters
├── tests/                          # All test files
│   ├── domain_tests/               # Tests for entities
│   ├── infrastructure_tests/       # Tests for repositories
│   └── usecases_tests/             # Tests for business logic
├── CMakeLists.txt                  # Main build configuration
└── vcpkg.json                      # Dependency management
```
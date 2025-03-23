#include "usecases/user_service.hpp"
#include <memory>
#include <iostream>

#include "persistence/in_memory_user_repository.hpp"
#include "server/rest_server.hpp"


std::shared_ptr<UserRepository> createRepository() {
    return std::make_shared<infrastructure::persistence::InMemoryUserRepository>();
}

std::shared_ptr<UserService> createUserService(const std::shared_ptr<UserRepository> &userRepository) {
    return std::make_shared<UserService>(userRepository);
}

int main() {
    std::cout << "Initializing REST API server..." << std::endl;

    try {

        const auto userRepository = createRepository();

        const User user1{1, "John Doe", "john@example.com"};
        const User user2{2, "Jane Smith", "jane@example.com"};
        const User user3{3, "Robert Müller", "robert@example.com"};

        userRepository->addUser(user1);
        userRepository->addUser(user2);
        userRepository->addUser(user3);

        const auto userService = createUserService(userRepository);

        constexpr uint16_t port = 8080;
        interfaces::rest::server::RestServer server(userService);

        std::cout << "Starting REST API server on port " << port << std::endl;
        std::cout << "Available endpoints:" << std::endl;
        std::cout << " - GET    /api/users" << std::endl;
        std::cout << " - GET    /api/users/{id}" << std::endl;
        std::cout << " - POST   /api/users" << std::endl;
        std::cout << " - PUT    /api/users/{id}" << std::endl;
        std::cout << " - DELETE /api/users/{id}" << std::endl;

        server.start(port);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

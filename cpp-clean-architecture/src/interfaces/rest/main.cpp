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

    const auto userRepository = createRepository();

    userRepository->addUser(User(1, "John Doe", "john@example.com"));
    userRepository->addUser(User(2, "Jane Smith", "jane@example.com"));
    userRepository->addUser(User(3, "Robert Müller", "robert@example.com"));

    const auto userService = createUserService(userRepository);

    interfaces::rest::server::RestServer server(userService);
    server.start(8080);

    return 0;
}

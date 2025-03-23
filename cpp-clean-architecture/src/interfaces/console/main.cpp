#include <iostream>
#include <memory>
#include "core/domain/entities/user.hpp"
#include "core/domain/repositories/user_repository.hpp"
#include "infrastructure/persistence/in_memory_user_repository.hpp"
#include "core/usecases/user_service.hpp"

int main() {
    const std::shared_ptr<UserRepository> userRepository = std::make_shared<InMemoryUserRepository>();
    const UserService userService(userRepository);

    userRepository->addUser(User(1, "Alice", "alice@example.com"));
    userRepository->addUser(User(2, "Bob", "bob@example.com"));

    const auto users = userService.getAllUsers();
    std::ranges::copy(users, std::ostream_iterator<User>(std::cout, "\n"));

    return 0;
}

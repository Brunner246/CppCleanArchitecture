//
// Created by brunn on 23/03/2025.
//

#include "user_service.hpp"


UserService::UserService(std::shared_ptr<UserRepository> userRepository)
    : userRepository(std::move(userRepository)) {
}

std::vector<User> UserService::getAllUsers() const {
    return this->userRepository->findAllUsers();
}

std::optional<User> UserService::getUserById(const int id) const {
    return this->userRepository->findUserById(id);
}

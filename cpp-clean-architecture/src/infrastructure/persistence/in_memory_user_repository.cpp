//
// Created by brunn on 23/03/2025.
//

#include "in_memory_user_repository.hpp"
#include <ranges>
#include <algorithm>

void InMemoryUserRepository::addUser(const User &user) {
    users_.push_back(user);
}

std::optional<User> InMemoryUserRepository::findUserById(int id) const {
    if (const auto result = std::ranges::find_if(users_,
                                                 [id](const User &user) {
                                                     return user.getId() == id;
                                                 });
        result != users_.end()) {
        return *result;
    }
    return std::nullopt;
}

std::vector<User> InMemoryUserRepository::findAllUsers() const {
    return users_;
}

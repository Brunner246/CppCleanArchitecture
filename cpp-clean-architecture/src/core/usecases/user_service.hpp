#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP

#include <memory>
#include <vector>

#include "core/domain/entities/user.hpp"
#include "domain/repositories/user_repository.hpp"
#include "include/core_export.h"


class CORE_API UserService {
public:
    explicit UserService(std::shared_ptr<UserRepository> userRepository);

    [[nodiscard]] std::vector<User> getAllUsers() const;

    [[nodiscard]] std::optional<User> getUserById(int id) const;

    void createUser(const User& user) const;

    [[nodiscard]] std::optional<User> updateUser(const User& user) const;

    [[nodiscard]] bool deleteUser(const User& user) const;

private:
    std::shared_ptr<UserRepository> userRepository{};
};

#endif // USER_SERVICE_HPP
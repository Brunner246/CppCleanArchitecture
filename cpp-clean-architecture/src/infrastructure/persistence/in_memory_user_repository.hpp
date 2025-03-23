#ifndef IN_MEMORY_USER_REPOSITORY_HPP
#define IN_MEMORY_USER_REPOSITORY_HPP

#include <vector>
#include <optional>
#include <user_repository.hpp>
#include <user.hpp>
#include "infrastructure_export.h"

class INFRASTRUCTURE_API InMemoryUserRepository final : public UserRepository {
public:
    void addUser(const User &user) override;

    [[nodiscard]] std::optional<User> findUserById(int id) const override;

    [[nodiscard]] std::vector<User> findAllUsers() const override;

private:
    std::vector<User> users_;
};

#endif // IN_MEMORY_USER_REPOSITORY_HPP
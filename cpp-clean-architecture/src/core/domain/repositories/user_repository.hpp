// user_repository.hpp

#ifndef USER_REPOSITORY_HPP
#define USER_REPOSITORY_HPP

#include <vector>
#include <optional>
#include "core/domain/entities/user.hpp"
#include "include/core_export.h"

class CORE_API UserRepository {
public:
    virtual ~UserRepository() = default;

    virtual void addUser(const User& user) = 0;

    virtual User updateUser(const User &user) = 0;

    [[nodiscard]] virtual std::optional<User> findUserById(int id) const = 0;

    [[nodiscard]] virtual std::vector<User> findAllUsers() const = 0;

    virtual bool deleteUser(int id) = 0;
};

#endif // USER_REPOSITORY_HPP
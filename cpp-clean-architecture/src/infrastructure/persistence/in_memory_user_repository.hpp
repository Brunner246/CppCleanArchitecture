#ifndef IN_MEMORY_USER_REPOSITORY_HPP
#define IN_MEMORY_USER_REPOSITORY_HPP

#include <vector>
#include <optional>

#include "core/domain/entities/user.hpp"
#include "domain/repositories/user_repository.hpp"

#include "include/Infrastructure_export.h"

namespace infrastructure::persistence
{
    class INFRASTRUCTURE_API InMemoryUserRepository final : public UserRepository {
    public:
        void addUser(const User &user) override;

        [[nodiscard]] std::optional<User> findUserById(int id) const override;

        [[nodiscard]] std::vector<User> findAllUsers() const override;

        User updateUser(const User &user) override;

        bool deleteUser(int id) override;

    private:
        std::vector<User> users_;
    };

}


#endif // IN_MEMORY_USER_REPOSITORY_HPP
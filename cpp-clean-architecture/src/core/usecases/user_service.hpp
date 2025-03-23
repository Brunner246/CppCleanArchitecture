#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP

#include <memory>
#include <vector>

#include "user.hpp"
#include "user_repository.hpp"
#include "core_export.h"


class CORE_API UserService {
public:
    explicit UserService(std::shared_ptr<UserRepository> userRepository);

    [[nodiscard]] std::vector<User> getAllUsers() const;
    [[nodiscard]] std::optional<User> getUserById(int id) const;

private:
    std::shared_ptr<UserRepository> userRepository{};
};

#endif // USER_SERVICE_HPP
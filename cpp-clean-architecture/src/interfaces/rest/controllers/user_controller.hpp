#pragma once

#include <crow.h>
#include <memory>
#include <crow/middlewares/cors.h>

#include "usecases/user_service.hpp"

namespace interfaces::rest::controllers {

class UserController {
public:
    explicit UserController(std::shared_ptr<UserService> userService);

    void registerRoutes(crow::App<crow::CORSHandler> &app) const;

private:
    std::shared_ptr<UserService> userService;

    crow::response getUserById(const crow::request& req, uint64_t id) const;

    crow::response getAllUsers(const crow::request& req) const;

    crow::response createUser(const crow::request& req) const;

    crow::response updateUser(const crow::request& req, uint64_t id) const;

    crow::response deleteUser(const crow::request& req, uint64_t id) const;
};

} // namespace interfaces::rest::controllers
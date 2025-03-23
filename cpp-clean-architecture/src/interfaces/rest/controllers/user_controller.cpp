#include "user_controller.hpp"
#include <nlohmann/json.hpp>
#include "user_adapter.hpp"


namespace interfaces::rest::controllers {
    UserController::UserController(std::shared_ptr<UserService> userService)
        : userService(std::move(userService)) {
    }

    void UserController::registerRoutes(crow::App<crow::CORSHandler> &app) const {
        CROW_ROUTE(app, "/api/users/<uint>")
                .methods(crow::HTTPMethod::GET)
                ([this](const crow::request &req, const uint64_t id) {
                    return getUserById(req, id);
                });

        CROW_ROUTE(app, "/api/users")
                .methods(crow::HTTPMethod::GET)
                ([this](const crow::request &req) {
                    return getAllUsers(req);
                });

        CROW_ROUTE(app, "/api/users")
                .methods(crow::HTTPMethod::POST)
                ([this](const crow::request &req) {
                    return createUser(req);
                });

        CROW_ROUTE(app, "/api/users/<uint>")
                .methods(crow::HTTPMethod::PUT)
                ([this](const crow::request &req, const uint64_t id) {
                    return updateUser(req, id);
                });

        CROW_ROUTE(app, "/api/users/<uint>")
                .methods(crow::HTTPMethod::Delete)
                ([this](const crow::request &req, const uint64_t id) {
                    return deleteUser(req, id);
                });
    }

    crow::response UserController::getUserById(const crow::request &req, uint64_t id) const {
        std::ignore = req;
        try {
            const auto user = userService->getUserById(static_cast<int>(id));
            if (!user) {
                return crow::response(404, std::format("User with id {} not found", id));
            }

            auto dto = adapters::UserAdapter::toDto(*user);
            const nlohmann::json json = dto;
            return crow::response(200, json.dump());
        } catch (const std::exception &e) {
            return crow::response(500, std::format("Server error: {}", e.what()));
        }
    }

    crow::response UserController::getAllUsers(const crow::request &req) const {
        std::ignore = req;
        try {
            const auto users = userService->getAllUsers();
            nlohmann::json json = nlohmann::json::array();

            for (const auto &user: users) {
                auto dto = adapters::UserAdapter::toDto(user);
                json.push_back(dto);
            }

            return crow::response(200, json.dump());
        } catch (const std::exception &e) {
            return crow::response(500, std::format("Server error: {}", e.what()));
        }
    }

    crow::response UserController::createUser(const crow::request &req) const {
        try {
            const auto reqBody = nlohmann::json::parse(req.body);
            const interfaces::rest::dto::UserDto userDto = reqBody;

            const auto user = adapters::UserAdapter::toDomain(userDto);
            userService->createUser(user); // return User from create user

            auto createdUserDto = adapters::UserAdapter::toDto(user);
            const nlohmann::json json = createdUserDto;

            return crow::response(201, json.dump());
        } catch (const nlohmann::json::exception &e) {
            return crow::response(400, std::format("Invalid JSON: {}", e.what()));
        } catch (const std::exception &e) {
            return crow::response(500, std::format("Server error: {}", e.what()));
        }
    }

    crow::response UserController::updateUser(const crow::request &req, uint64_t id) const {
        try {
            auto reqBody = nlohmann::json::parse(req.body);
            interfaces::rest::dto::UserDto userDto = reqBody;

            if (userDto.id != id) {
                return crow::response(400, "ID in URL does not match ID in body");
            }

            auto user = adapters::UserAdapter::toDomain(userDto);
            auto updatedUser = userService->updateUser(user);

            if (!updatedUser) {
                return crow::response(404, std::format("User with id {} not found", id));
            }

            auto updatedUserDto = adapters::UserAdapter::toDto(*updatedUser);
            nlohmann::json json = updatedUserDto;

            return crow::response(200, json.dump());
        } catch (const nlohmann::json::exception &e) {
            return crow::response(400, std::format("Invalid JSON: {}", e.what()));
        } catch (const std::exception &e) {
            return crow::response(500, std::format("Server error: {}", e.what()));
        }
    }

    crow::response UserController::deleteUser(const crow::request &req, uint64_t id) const {
        std::ignore = req;
        try {
            if (const auto user = userService->getUserById(static_cast<int>(id))) {
                if (const bool success = userService->deleteUser(*user);
                    !success) {
                    return crow::response(404, std::format("User with id {} not found", id));
                }

                return crow::response(204);
            }
        } catch (const std::exception &e) {
            return crow::response(500, std::format("Server error: {}", e.what()));
        }
        return crow::response(404, std::format("User with id {} not found", id));
    }
} // namespace interfaces::rest::controllers

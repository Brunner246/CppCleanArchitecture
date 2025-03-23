#include "user_controller.hpp"

#include "adapters/user_adapter.hpp"
#include <nlohmann/json.hpp>

namespace interfaces::rest::controllers {
    UserController::UserController(std::shared_ptr<UserService> userService)
        : userService(std::move(userService)) {
    }

    std::vector<Route> UserController::getRoutes() {
        return {
            {"/api/users", "GET", [this](const HttpRequest &req) { return getAllUsers(req); }},
            {"/api/users", "POST", [this](const HttpRequest &req) { return createUser(req); }},
            {
                "/api/users/:id", "GET", [this](const HttpRequest &req) {
                    const auto id = getIdParam(req, "id");
                    if (!id) {
                        return HttpResponse{400, "Invalid ID parameter"};
                    }
                    return getUserById(req, *id);
                }
            },
            {
                "/api/users/:id", "PUT", [this](const HttpRequest &req) {
                    const auto id = getIdParam(req, "id");
                    if (!id) {
                        return HttpResponse{400, "Invalid ID parameter"};
                    }
                    return updateUser(req, *id);
                }
            },
            {
                "/api/users/:id", "DELETE", [this](const HttpRequest &req) {
                    const auto id = getIdParam(req, "id");
                    if (!id) {
                        return HttpResponse{400, "Invalid ID parameter"};
                    }
                    return deleteUser(req, *id);
                }
            }
        };
    }

    HttpResponse UserController::getUserById(const HttpRequest &req, const uint64_t id) const {
        std::ignore = req;
        try {
            const auto user = userService->getUserById(static_cast<int>(id));
            if (!user) {
                return HttpResponse{404, "User not found"};
            }

            auto dto = adapters::UserAdapter::toDto(*user);
            const nlohmann::json json = dto;
            return HttpResponse{200, json.dump()};
        } catch (const std::exception &e) {
            return HttpResponse{500, std::string("Server error: ") + e.what()};
        }
    }

    HttpResponse UserController::getAllUsers(const HttpRequest &req) const {
        std::ignore = req;
        try {
            const auto users = userService->getAllUsers();
            nlohmann::json json = nlohmann::json::array();

            for (const auto &user: users) {
                auto dto = adapters::UserAdapter::toDto(user);
                json.push_back(dto);
            }

            return HttpResponse{200, json.dump()};
        } catch (const std::exception &e) {
            return HttpResponse{500, std::string("Server error: ") + e.what()};
        }
    }

    HttpResponse UserController::createUser(const HttpRequest &req) const {
        try {
            const auto userDto = parseUserDto(req.body);
            if (!userDto) {
                return HttpResponse{400, "Invalid user data"};
            }

            const auto user = adapters::UserAdapter::toDomain(*userDto);
            userService->createUser(user);

            auto createdUserDto = adapters::UserAdapter::toDto(user);
            const nlohmann::json json = createdUserDto;

            return HttpResponse{201, json.dump()};
        } catch (const std::exception &e) {
            return HttpResponse{500, std::string("Server error: ") + e.what()};
        }
    }

    HttpResponse UserController::updateUser(const HttpRequest &req, uint64_t id) const {
        try {
            auto userDto = parseUserDto(req.body);
            if (!userDto) {
                return HttpResponse{400, "Invalid user data"};
            }

            if (userDto->id != static_cast<int>(id)) {
                return HttpResponse{400, "ID in URL does not match ID in body"};
            }

            auto user = adapters::UserAdapter::toDomain(*userDto);
            auto updatedUser = userService->updateUser(user);

            if (!updatedUser) {
                return HttpResponse{404, "User not found"};
            }

            auto updatedUserDto = adapters::UserAdapter::toDto(*updatedUser);
            nlohmann::json json = updatedUserDto;

            return HttpResponse{200, json.dump()};
        } catch (const std::exception &e) {
            return HttpResponse{500, std::string("Server error: ") + e.what()};
        }
    }

    HttpResponse UserController::deleteUser(const HttpRequest &req, uint64_t id) const {
        std::ignore = req;
        try {
            if (const auto user = userService->getUserById(static_cast<int>(id))) {
                if (const bool success = userService->deleteUser(*user);
                    !success) {
                    return HttpResponse(404, std::format("User with id {} not found", id));
                }

                return HttpResponse{204, ""};
            }
        } catch (const std::exception &e) {
            return HttpResponse{500, std::string("Server error: ") + e.what()};
        }
        return HttpResponse{404, "User not found"};
    }

    std::optional<uint64_t> UserController::getIdParam(const HttpRequest &req, const std::string &paramName) {
        const auto it = req.params.find(paramName);
        if (it == req.params.end()) {
            return std::nullopt;
        }

        try {
            return std::stoull(it->second);
        } catch (...) {
            return std::nullopt;
        }
    }

    std::optional<dto::UserDto> UserController::parseUserDto(const std::string &body) {
        try {
            const auto json = nlohmann::json::parse(body);
            return json.get<dto::UserDto>();
        } catch (...) {
            return std::nullopt;
        }
    }
} // namespace interfaces::rest::controllers

#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <optional>
#include <string>

#include "usecases/user_service.hpp"
#include "interfaces/rest/dto/user_dto.hpp"

namespace interfaces::rest::controllers {

struct HttpRequest {
    std::string body;
    std::string path;
    std::string method;
    std::unordered_map<std::string, std::string> params;
    std::unordered_map<std::string, std::string> headers;
};

struct HttpResponse {
    int status_code = 200;
    std::string body;
    std::unordered_map<std::string, std::string> headers;
};

using RouteHandler = std::function<HttpResponse(const HttpRequest&)>;

struct Route {
    std::string path;
    std::string method;
    RouteHandler handler;
};

class UserController {
public:
    explicit UserController(std::shared_ptr<UserService> userService);

    std::vector<Route> getRoutes();

private:
    std::shared_ptr<UserService> userService;

    HttpResponse getUserById(const HttpRequest& req, uint64_t id) const;
    HttpResponse getAllUsers(const HttpRequest& req) const;
    HttpResponse createUser(const HttpRequest& req) const;
    HttpResponse updateUser(const HttpRequest& req, uint64_t id) const;
    HttpResponse deleteUser(const HttpRequest& req, uint64_t id) const;

    static std::optional<uint64_t> getIdParam(const HttpRequest& req, const std::string& paramName);

    static std::optional<dto::UserDto> parseUserDto(const std::string& body);
};

} // namespace interfaces::rest::controllers
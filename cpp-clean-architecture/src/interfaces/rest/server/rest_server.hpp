#pragma once

#include <memory>
#include <crow.h>
#include <crow/middlewares/cors.h>
#include "usecases/user_service.hpp"
#include "interfaces/rest/controllers/user_controller.hpp"

namespace interfaces::rest::server {

class RestServer {
public:
    explicit RestServer(std::shared_ptr<UserService> userService);
    
    void start(std::uint16_t port = 8080);

private:
    crow::App<crow::CORSHandler> app;
    std::unique_ptr<controllers::UserController> userController;
};

} // namespace interfaces::rest::server

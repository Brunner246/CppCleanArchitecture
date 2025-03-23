#pragma once

#include <memory>
#include <crow.h>
#include <crow/middlewares/cors.h>

#include "interfaces/rest/controllers/user_controller.hpp"
#include "usecases/user_service.hpp"


// https://github.com/CrowCpp/Crow/blob/master/examples/middlewares/example_session.cpp

namespace interfaces::rest::server {
    class RestServer {
    public:
        explicit RestServer(std::shared_ptr<UserService> userService);

        void start(uint16_t port = 8080);

    private:
        crow::App<crow::CORSHandler> app;
        std::unique_ptr<rest::controllers::UserController> userController;
    };
} // namespace interfaces::rest::server

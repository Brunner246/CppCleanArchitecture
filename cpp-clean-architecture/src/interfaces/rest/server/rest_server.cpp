#include "rest_server.hpp"
#include <iostream>

namespace interfaces::rest::server {

    RestServer::RestServer(std::shared_ptr<UserService> userService)
        : userController(std::make_unique<rest::controllers::UserController>(userService)) {

        auto &cors = app.get_middleware<crow::CORSHandler>();
        cors
                .global()
                .headers("Content-Type", "Authorization")
                .methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST,
                         crow::HTTPMethod::PUT, crow::HTTPMethod::Delete)
                .origin("*");

        userController->registerRoutes(app);
    }

    void RestServer::start(const uint16_t port) {
        std::cout << "Starting REST server on port " << port << std::endl;
        app.port(port).multithreaded().run();
    }
} // namespace interfaces::rest::server

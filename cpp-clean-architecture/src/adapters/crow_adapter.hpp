#pragma once

#include <crow.h>
#include <crow/middlewares/cors.h>
#include "interfaces/rest/controllers/user_controller.hpp" //TODO make rest server a shared library !!!

#include <include/Adapters_export.h>

namespace interfaces::rest::adapters {

class ADAPTERS_API CrowAdapter {
public:
    static void registerRoutes(crow::App<crow::CORSHandler>& app, controllers::UserController& controller);
    
private:
    static controllers::HttpRequest convertRequest(const crow::request& req);

    static crow::response convertResponse(const controllers::HttpResponse& resp);
};

} // namespace interfaces::rest::adapters
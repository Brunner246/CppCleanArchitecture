#include "crow_adapter.hpp"
#include <nlohmann/json.hpp>

namespace interfaces::rest::adapters {

void CrowAdapter::registerRoutes(crow::App<crow::CORSHandler>& app, controllers::UserController& controller) {
    for (const auto routes = controller.getRoutes(); const auto& route : routes) {
        if (route.path == "/api/users" && route.method == "GET") {
            CROW_ROUTE(app, "/api/users")
                .methods(crow::HTTPMethod::GET)
                ([&controller](const crow::request& req) {
                    const auto httpReq = convertRequest(req);
                    const auto httpResp = controller.getRoutes()[0].handler(httpReq);
                    return convertResponse(httpResp);
                });
        }
        else if (route.path == "/api/users" && route.method == "POST") {
            CROW_ROUTE(app, "/api/users")
                .methods(crow::HTTPMethod::POST)
                ([&controller](const crow::request& req) {
                    const auto httpReq = convertRequest(req);
                    const auto httpResp = controller.getRoutes()[1].handler(httpReq);
                    return convertResponse(httpResp);
                });
        }
        else if (route.path == "/api/users/:id" && route.method == "GET") {
            CROW_ROUTE(app, "/api/users/<uint>")
                .methods(crow::HTTPMethod::GET)
                ([&controller](const crow::request& req, uint64_t id) {
                    auto httpReq = convertRequest(req);
                    httpReq.params["id"] = std::to_string(id);
                    const auto httpResp = controller.getRoutes()[2].handler(httpReq);
                    return convertResponse(httpResp);
                });
        }
        else if (route.path == "/api/users/:id" && route.method == "PUT") {
            CROW_ROUTE(app, "/api/users/<uint>")
                .methods(crow::HTTPMethod::PUT)
                ([&controller](const crow::request& req, uint64_t id) {
                    auto httpReq = convertRequest(req);
                    httpReq.params["id"] = std::to_string(id);
                    const auto httpResp = controller.getRoutes()[3].handler(httpReq);
                    return convertResponse(httpResp);
                });
        }
        else if (route.path == "/api/users/:id" && route.method == "DELETE") {
            CROW_ROUTE(app, "/api/users/<uint>")
                .methods(crow::HTTPMethod::Delete)
                ([&controller](const crow::request& req, uint64_t id) {
                    auto httpReq = convertRequest(req);
                    httpReq.params["id"] = std::to_string(id);
                    const auto httpResp = controller.getRoutes()[4].handler(httpReq);
                    return convertResponse(httpResp);
                });
        }
    }
}

controllers::HttpRequest CrowAdapter::convertRequest(const crow::request& req) {
    controllers::HttpRequest httpReq;
    httpReq.body = req.body;
    httpReq.path = req.url;

    switch(req.method) {
        case crow::HTTPMethod::GET:
            httpReq.method = "GET";
        break;
        case crow::HTTPMethod::POST:
            httpReq.method = "POST";
        break;
        case crow::HTTPMethod::PUT:
            httpReq.method = "PUT";
        break;
        case crow::HTTPMethod::Delete:
            httpReq.method = "DELETE";
        break;
        case crow::HTTPMethod::HEAD:
            httpReq.method = "HEAD";
        break;
        case crow::HTTPMethod::PATCH:
            httpReq.method = "PATCH";
        break;
        case crow::HTTPMethod::OPTIONS:
            httpReq.method = "OPTIONS";
        break;
        default:
            httpReq.method = "UNKNOWN";
        break;
    }

    // convert headers
    for (const auto& [key, value] : req.headers) {
        httpReq.headers[key] = value;
    }
    
    return httpReq;
}

crow::response CrowAdapter::convertResponse(const controllers::HttpResponse& resp) {
    crow::response crowResp(resp.status_code, resp.body);
    
    // Set headers
    for (const auto& [key, value] : resp.headers) {
        crowResp.set_header(key, value);
    }
    
    return crowResp;
}

} // namespace interfaces::rest::adapters
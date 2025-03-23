#include "user_dto.hpp"

namespace interfaces::rest::dto {

void to_json(nlohmann::json& j, const UserDto& user) {
    j = nlohmann::json{
        {"id", user.id},
        {"name", user.name},
        {"email", user.email}
    };
}

void from_json(const nlohmann::json& j, UserDto& user) {
    j.at("id").get_to(user.id);
    j.at("name").get_to(user.name);
    j.at("email").get_to(user.email);
}

} // namespace interfaces::rest::dto
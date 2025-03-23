#pragma once

#include <string>
#include <cstdint>
#include <nlohmann/json.hpp>

namespace interfaces::rest::dto {

struct UserDto {
    int id;
    std::string name;
    std::string email;
};


void to_json(nlohmann::json& j, const UserDto& user);
void from_json(const nlohmann::json& j, UserDto& user);

} // namespace interfaces::rest::dto
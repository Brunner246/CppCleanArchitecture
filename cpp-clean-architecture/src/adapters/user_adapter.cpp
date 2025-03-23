#include "user_adapter.hpp"

namespace adapters {

User UserAdapter::toDomain(const interfaces::rest::dto::UserDto& dto) {
    return User(dto.id, dto.name, dto.email);
}

interfaces::rest::dto::UserDto UserAdapter::toDto(const User& user) {
    return interfaces::rest::dto::UserDto{
        .id = user.getId(),
        .name = user.getName(),
        .email = user.getEmail()
    };
}

} // namespace adapters
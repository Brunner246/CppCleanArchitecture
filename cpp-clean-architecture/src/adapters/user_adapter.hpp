#pragma once

#include <include/Adapters_export.h>

#include "domain/entities/user.hpp"
#include "interfaces/rest/dto/user_dto.hpp"


namespace adapters {
    class ADAPTERS_API UserAdapter {
    public:
        static User toDomain(const interfaces::rest::dto::UserDto &dto);

        static interfaces::rest::dto::UserDto toDto(const User &user);
    };
} // namespace adapters

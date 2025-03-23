#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "include/core_export.h"

class CORE_API User {
public:
    explicit User(int id, std::string name, std::string email);

    [[nodiscard]] int getId() const;

    [[nodiscard]] std::string getName() const;
    void setName(std::string name);

    [[nodiscard]] std::string getEmail() const;
    void setEmail(std::string email);

    [[nodiscard]] bool operator==(const User &other) const;

    [[nodiscard]] bool operator!=(const User &other) const;

    [[nodiscard]] std::string toString() const;

    std::ostream& operator<<(std::ostream& os) const;

private:
    int id_;
    std::string name_;
    std::string email_;
};

CORE_API std::ostream& operator<<(std::ostream& os, const User& user);


// namespace std {
//     template<>
//     struct hash<User> {
//         std::size_t operator()(const User &user) const noexcept {
//             const std::size_t h1 = std::hash<int>{}(user.getId());
//             const std::size_t h2 = std::hash<std::string>{}(user.getName());
//             const std::size_t h3 = std::hash<std::string>{}(user.getEmail());
//             return h1 ^ (h2 << 1) ^ (h3 << 2);
//         }
//     };
// }

#endif // USER_HPP

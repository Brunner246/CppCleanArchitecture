//
// Created by brunn on 23/03/2025.
//

#include "user.hpp"

#include <format>
#include <utility>
#include <ostream>

User::User(const int id, std::string name, std::string email)
    : id_(id), name_(std::move(name)), email_(std::move(email)) {
}

int User::getId() const {
    return this->id_;
}

std::string User::getName() const {
    return this->name_;
}

void User::setName(std::string name) {
    this->name_ = std::move(name);
}

void User::setEmail(std::string email) {
    this->email_ = std::move(email);
}

std::string User::getEmail() const {
    return this->email_;
}

bool User::operator==(const User &other) const {
    return id_ == other.id_ && name_ == other.name_ && email_ == other.email_;
}

bool User::operator!=(const User &other) const {
    return !(*this == other);
}

std::string User::toString() const {
    return std::format("User(id_={}, name={}, email={})", id_, name_, email_);
}

std::ostream &User::operator<<(std::ostream &os) const {
    return os << this->toString();
}

std::ostream &operator<<(std::ostream &os, const User &user) {
    return os << user.toString();
}

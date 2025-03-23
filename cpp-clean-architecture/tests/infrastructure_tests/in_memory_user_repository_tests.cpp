#include <gtest/gtest.h>

#include "in_memory_user_repository.hpp"


class InMemoryUserRepositoryTests : public ::testing::Test {
protected:
    InMemoryUserRepository userRepository;

    void SetUp() override {
        userRepository.addUser(User(1, "John Doe", "john@example.com"));
        userRepository.addUser(User(2, "Jane Smith", "jane@example.com"));
    }
};

TEST_F(InMemoryUserRepositoryTests, FindUserById_ReturnsCorrectUser) {
    const auto user = userRepository.findUserById(1);
    ASSERT_TRUE(user.has_value());
    EXPECT_EQ(user->getId(), 1);
    EXPECT_EQ(user->getName(), "John Doe");
    EXPECT_EQ(user->getEmail(), "john@example.com");
}

TEST_F(InMemoryUserRepositoryTests, FindUserById_ReturnsEmpty_WhenUserNotFound) {
    const auto user = userRepository.findUserById(3);
    ASSERT_FALSE(user.has_value());
}

TEST_F(InMemoryUserRepositoryTests, FindAllUsers_ReturnsAllUsers) {
    const auto users = userRepository.findAllUsers();
    ASSERT_EQ(users.size(), 2);
    EXPECT_EQ(users[0].getId(), 1);
    EXPECT_EQ(users[1].getId(), 2);
}
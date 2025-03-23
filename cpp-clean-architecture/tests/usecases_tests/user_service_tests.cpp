#include <gtest/gtest.h>

#include "in_memory_user_repository.hpp"
#include "user_service.hpp"


class UserServiceTests : public ::testing::Test {
protected:
    std::shared_ptr<UserRepository> userRepository = std::make_shared<InMemoryUserRepository>();
    UserService userService{userRepository};

    void SetUp() override {
        userRepository->addUser(User{1, "John Doe", "john.doe@example.com"});
        userRepository->addUser(User{2, "Jane Smith", "jane.smith@example.com"});
    }
};

TEST_F(UserServiceTests, GetUserById_ReturnsCorrectUser) {
    const auto user = userService.getUserById(1);
    ASSERT_TRUE(user.has_value());
    EXPECT_EQ(user->getId(), 1);
    EXPECT_EQ(user->getName(), "John Doe");
    EXPECT_EQ(user->getEmail(), "john.doe@example.com");
}

TEST_F(UserServiceTests, GetUserById_ReturnsEmpty_WhenUserNotFound) {
    const auto user = userService.getUserById(3);
    ASSERT_FALSE(user.has_value());
}

TEST_F(UserServiceTests, GetAllUsers_ReturnsAllUsers) {
    const auto users = userService.getAllUsers();
    ASSERT_EQ(users.size(), 2);
    EXPECT_EQ(users[0].getId(), 1);
    EXPECT_EQ(users[1].getId(), 2);
}
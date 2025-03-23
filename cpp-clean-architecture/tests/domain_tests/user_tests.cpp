#include <gtest/gtest.h>
#include "user.hpp"

TEST(UserTests, UserCreation) {
    const User user(1, "John Doe", "john.doe@example.com");
    EXPECT_EQ(user.getId(), 1);
    EXPECT_EQ(user.getName(), "John Doe");
    EXPECT_EQ(user.getEmail(), "john.doe@example.com");
}

TEST(UserTests, UserSetName) {
    User user(1, "John Doe", "john.doe@example.com");
    user.setName("Jane Doe");
    EXPECT_EQ(user.getName(), "Jane Doe");
}

TEST(UserTests, UserSetEmail) {
    User user(1, "John Doe", "john.doe@example.com");
    user.setEmail("jane.doe@example.com");
    EXPECT_EQ(user.getEmail(), "jane.doe@example.com");
}
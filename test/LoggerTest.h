#include "gtest/gtest.h"
#include "gtest/internal/gtest-port.h"

#include "Logger.h"

#include <string>

using namespace std;

TEST(LoggerTest, NoticeLog) {
    string msg = "My test log message";
    testing::internal::CaptureStdout();

    Logger::notice(msg);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("<6> " + msg, output);
}

TEST(LoggerTest, InfoLog) {
    string msg = "My test log message";
    testing::internal::CaptureStdout();

    Logger::info(msg);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("<5> " + msg, output);
}

TEST(LoggerTest, WarnLog) {
    string msg = "My test log message";
    testing::internal::CaptureStdout();

    Logger::warn(msg);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("<4> " + msg, output);
}

TEST(LoggerTest, ErrorLog) {
    string msg = "My test log message";
    testing::internal::CaptureStdout();

    Logger::error(msg);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("<3> " + msg, output);
}

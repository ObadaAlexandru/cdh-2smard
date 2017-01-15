#include "gtest/gtest.h"
#include "CliParser.h"

#include <map>

using namespace std;

TEST(CliParserTest, ParseArguments) {
    CliParser cliParser;
    const char* argv[] = { "2smard",
                           "--config=testConfig.conf",
                           "--half_1=A12s|I13s|A10s",
                           "--half_2=A30s|I10s|A70s"};

    map<string, string> arguments = cliParser.getArguments(4, argv);


    EXPECT_EQ("testConfig.conf", arguments[CliParser::configPathKey]);
    EXPECT_EQ("A12s|I13s|A10s", arguments[CliParser::halfOneKey]);
    EXPECT_EQ("A30s|I10s|A70s", arguments[CliParser::halfTwoKey]);
}

TEST(CliParserTest, TooManyArguments) {
    CliParser cliParser;
    const char* argv[] = { "2smard",
                           "--config=testConfig.conf",
                           "--half_1=A12s|I13s|A10s",
                           "--half_2=A30s|I10s|A70s",
                           "--half_3=A33s|I10s"};

   EXPECT_ANY_THROW(cliParser.getArguments(5, argv));
}

TEST(CliParserTest, ArgumentWrongSynthax) {
    CliParser cliParser;
    const char* argv[] = { "2smard",
                           "--config testConfig.conf",
                           "--half_1 A12s|I13s|A10s",
                           "--half_3 A33s|I10s"};

   EXPECT_ANY_THROW(cliParser.getArguments(4, argv));
}

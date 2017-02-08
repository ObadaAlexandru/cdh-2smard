#include "gtest/gtest.h"
#include "ConfigParser.h"

#include <utility>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

void createFile(string path, string content) {
    ofstream outfile (path);
    outfile << content;
    outfile.close();
}

bool deleteFile(string path) {
    return remove(path.c_str()) == 0;
}

TEST(ConfigParserTest, parseConfigFile) {
    string testConfPath = "/tmp/testConfig.conf";
    string configContent = "half_1=A30s|I25s|A45s\n"
                           "half_2=A45s|I15s|A30s|I5m|A45s\n"
                           "pin_half_1=P30\n"
                           "pin_half_2=P31\n"
                           "activation_pin_half_1=P32\n"
                           "activation_pin_half_2=P33\n";
    createFile(testConfPath, configContent);
    ConfigParser configParser(testConfPath);

    map<string, string> configurations = configParser.getConfigs();

    EXPECT_EQ("A30s|I25s|A45s", configurations[ConfigParser::halfOneKey]);
    EXPECT_EQ("A45s|I15s|A30s|I5m|A45s", configurations[ConfigParser::halfTwoKey]);
    EXPECT_EQ("P30", configurations[ConfigParser::pinKeyHalfOne]);
    EXPECT_EQ("P31", configurations[ConfigParser::pinKeyHalfTwo]);
    EXPECT_EQ("P32", configurations[ConfigParser::pinKeyHalfOneActivation]);
    EXPECT_EQ("P33", configurations[ConfigParser::pinKeyHalfTwoActivation]);

    EXPECT_TRUE(deleteFile(testConfPath));
}

TEST(ConfigParserTest, CommentsAreCorrectlyInterpreted) {
    string testConfPath = "/tmp/testConfig.conf";
    string configContent = "#comment\n"
                           "# another comment\n"
                           "conf_1=value_1\n"
                           "# one more comment\n"
                           "conf_2=value_2\n";
    createFile(testConfPath, configContent);
    ConfigParser configParser(testConfPath);

    map<string, string> configurations = configParser.getConfigs();

    EXPECT_EQ("value_1", configurations["conf_1"]);
    EXPECT_EQ("value_2", configurations["conf_2"]);

    EXPECT_TRUE(deleteFile(testConfPath));
}

TEST(ConfigParserTest, SpacesArePartOfTheValue) {
    string testConfPath = "/tmp/testConfig.conf";
    string configContent = "conf_1= value_1\n"
                           "conf_2= value_2\n";
    createFile(testConfPath, configContent);
    ConfigParser configParser(testConfPath);

    map<string, string> configurations = configParser.getConfigs();

    EXPECT_EQ(" value_1", configurations["conf_1"]);
    EXPECT_NE("value_2", configurations["conf_2"]);

    EXPECT_TRUE(deleteFile(testConfPath));
}

TEST(ConfigParserTest, InvalidConfigLines) {
    string testConfPath = "/tmp/testConfig.conf";
    string configContent = "conf_1 value_1\n"
                           "conf_2=value_2=value_3\n";
    createFile(testConfPath, configContent);

    EXPECT_ANY_THROW(ConfigParser configParser(testConfPath));

    EXPECT_TRUE(deleteFile(testConfPath));
}

TEST(ConfigParserTest, GetCorrectSequencePair) {
    string testConfPath = "/tmp/testConfig.conf";
    string configContent = "half_1=A30s|I25s|A45s\n"
                           "half_2=A45s|I15s|A30s|I5m|A45s\n";
    createFile(testConfPath, configContent);
    ConfigParser configParser(testConfPath);

    pair<string, string> halfSequences = configParser.getSequences();

    EXPECT_EQ("A30s|I25s|A45s", halfSequences.first);
    EXPECT_EQ("A45s|I15s|A30s|I5m|A45s", halfSequences.second);

    EXPECT_TRUE(deleteFile(testConfPath));
}


TEST(ConfigParserTest, ConfigWithEmptyLine) {
  string testConfPath = "/tmp/testConfig.conf";
  string configContent = "half_1=A30s|I25s|A45s\n"
                         "half_2=A45s|I15s|A30s|I5m|A45s\n"
                         ""
                         "      ";
  createFile(testConfPath, configContent);
  ConfigParser configParser(testConfPath);

  pair<string, string> halfSequences = configParser.getSequences();

  EXPECT_EQ("A30s|I25s|A45s", halfSequences.first);
  EXPECT_EQ("A45s|I15s|A30s|I5m|A45s", halfSequences.second);

  EXPECT_TRUE(deleteFile(testConfPath));
}

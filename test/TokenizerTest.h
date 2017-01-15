#include "gtest/gtest.h"
#include "Tokenizer.h"

using namespace std;

TEST(TokenizerTest, SplitsStringInTokens) {
    string toBeTokenized = "this^is^my^string";
    Tokenizer tokenizer;

    vector<string> tokens = tokenizer.tokenize(toBeTokenized, "^");

    EXPECT_EQ(4, tokens.size());
    EXPECT_EQ("this", tokens[0]);
    EXPECT_EQ("is", tokens[1]);
    EXPECT_EQ("my", tokens[2]);
    EXPECT_EQ("string", tokens[3]);
}

TEST(TokenizerTest, NoDelimiterFound) {
    string toBeTokenized = "this^is^my^string";
    Tokenizer tokenizer;

    vector<string> tokens = tokenizer.tokenize(toBeTokenized, "|");
    for(string token: tokens) {
        cout << token << endl;
    }
    EXPECT_EQ(1, tokens.size());
    EXPECT_EQ(toBeTokenized, tokens[0]);
}

TEST(TokenizerTest, EmptyString) {
    string toBeTokenized = "";
    Tokenizer tokenizer;

    vector<string> tokens = tokenizer.tokenize(toBeTokenized, "|");

    EXPECT_TRUE(tokens.empty());
}

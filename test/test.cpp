#include <algorithm>
#include <list>

#include "gtest/gtest.h"
#include "SequenceParser.h"

TEST(SequenceParserTest, test) {
    SequenceParser sequenceParser;

    sequenceParser.getSequenceFromString("A300m|I4000s|A4040s|I300s");
}

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

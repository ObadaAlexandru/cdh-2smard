#include "gtest/gtest.h"
#include "SequenceParser.h"
#include "SequenceItem.h"

#include <algorithm>
#include <list>
#include <string>

TEST(SequenceParserTest, ParseSequenceString) {
    SequenceParser sequenceParser;
    std::string testSeq = "A10s|A10s|A10s";

    std::list<SequenceItem> sequenceItems = sequenceParser.getSequenceFromString(testSeq);

    EXPECT_EQ(3, sequenceItems.size());
    for(SequenceItem item : sequenceItems) {
          EXPECT_TRUE(item.isActive());
          EXPECT_EQ(10, item.getPeriod());
    }
}

TEST(SequenceParserTest, ThrowExceptionWhenInvalidSequence) {
   SequenceParser sequenceParser;
   std::string testSeq = "invalidSequence";
   std::string emptySeq = "";

   EXPECT_ANY_THROW(sequenceParser.getSequenceFromString(testSeq));
   EXPECT_ANY_THROW(sequenceParser.getSequenceFromString(emptySeq));
}

TEST(SequenceParserTest, MinuteToSecondsAreCorrectlyConverted) {
  SequenceParser sequenceParser;
  std::string testSeq = "I10m|I10m|I10m";

  std::list<SequenceItem> sequenceItems = sequenceParser.getSequenceFromString(testSeq);

  EXPECT_EQ(3, sequenceItems.size());
  for(SequenceItem item : sequenceItems) {
        EXPECT_FALSE(item.isActive());
        EXPECT_EQ(10*60, item.getPeriod());
  }
}

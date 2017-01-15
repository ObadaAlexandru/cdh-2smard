#include "gtest/gtest.h"

#include "SequenceParserTest.h"
#include "CliParserTest.h"
#include "ConfigParserTest.h"
#include "TokenizerTest.h"

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

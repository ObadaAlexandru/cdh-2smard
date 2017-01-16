#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>

/**
 * Tokenize a string by a delimiter
 */
class Tokenizer {
public:
    /**
     * Given a string "this#is#my#string" and a delimiter "#" the following tokens will be produced: [this, is, my, string]
     * @param toTokenize string to be tokenized
     * @param delimiter the separator by which the string should be split
     * @return a vector of tokens
     */
    std::vector<std::string> tokenize(const std::string& toTokenize, const std::string& delimiter);
};
#endif

#include "Tokenizer.h"

using namespace std;

vector<string> Tokenizer::tokenize(const string &toTokenize, const string &delimiter) {
    vector<string> tokens;
    string::size_type lastPos = toTokenize.find_first_not_of(delimiter, 0);
    string::size_type pos = toTokenize.find_first_of(delimiter, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(toTokenize.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = toTokenize.find_first_not_of(delimiter, pos);
        // Find next "non-delimiter"
        pos = toTokenize.find_first_of(delimiter, lastPos);
    }
    return tokens;
}

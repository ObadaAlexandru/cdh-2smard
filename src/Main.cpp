#include "SequenceParser.h"
#include "ConfigParser.h"
#include "Tokenizer.h"

#include <iostream>
#include <utility>

using namespace std;

#define DEFAULT_CONFIG_PATH "./config.cfg"
#define DEFAULT_SEQUENCE "A300m|I4000s|A4040s|I300s"

void printSequence(list<SequenceItem> sequence) {
	for(SequenceItem item: sequence) {
		cout << item.getPeriod() << endl;
	}
}

map<string, string> parseCli(int argc, const char* argv[]) {
	map<string, string> arguments;
	for(int i = 1; i < argc - 1; i++) {
		arguments[argv[i]] = argv[i+1];
		cout << argv[i] << "=" << argv[i+1] << "\n";
	}
	return arguments;
}

int main(int argc, const char* argv[])
{
	if(argc > 1) {
		cout << "Command line arguments provided\n";
		parseCli(argc, argv);
	}
	SequenceParser sequenceParser;
	list<SequenceItem> items = sequenceParser.getSequenceFromString("A300m|I4000s|123123|123123|123123");
	for(SequenceItem item: items) {
		cout << item.getPeriod() << endl;
	}

	ConfigParser configParser(DEFAULT_CONFIG_PATH);
	pair<string, string> configs = configParser.getSequences();
	printSequence(sequenceParser.getSequenceFromString(configs.first));
	printSequence(sequenceParser.getSequenceFromString(configs.second));
	return 0;
}

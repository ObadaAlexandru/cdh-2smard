#include "SequenceParser.h"
#include "ConfigParser.h"
#include "Tokenizer.h"
#include "CliParser.h"
#include "SequenceRunner.h"

#include <iostream>
#include <utility>
#include <csignal>

using namespace std;

#define DEFAULT_CONFIG_PATH "./config.cfg"

void printSequence(list<SequenceItem> sequence) {
	for(SequenceItem item: sequence) {
		cout << item.getPeriod() << endl;
	}
}

map<string, string> getCliArguments(int argc, const char* argv[]) {
		CliParser cliParser;
		map<string, string> cliArguments;
		if(argc > 1) {
			cout << "Command line arguments provided\n";
			cliArguments = cliParser.getArguments(argc, argv);
		}
		return cliArguments;
}

string getConfigFilePath(const map<string, string> &cliArguments) {
		if(cliArguments.count(CliParser::configPathKey) != 0) {
				return cliArguments.find(CliParser::configPathKey)->second;
		}
		return DEFAULT_CONFIG_PATH;
}

void signalHandler(int signal) {
		cout<< "Shutting down ..."<<signal<<endl;
		SequenceRunner::stopRun();
}

pair<list<SequenceItem>, list<SequenceItem>> getSequences(ConfigParser &configParser, const map<string, string> &cliArguments) {
		SequenceParser sequenceParser;
		pair<string, string> sequences = configParser.getSequences();

		if(cliArguments.count(CliParser::halfOneKey) != 0) {
			cout << "Override first half with = "<< cliArguments.find(CliParser::halfOneKey)->second << "\n";
			sequences.first = cliArguments.find(CliParser::halfOneKey)->second;
		}

		if(cliArguments.count(CliParser::halfTwoKey) != 0) {
			cout << "Override second half with = " << cliArguments.find(CliParser::halfTwoKey)->second << "\n";
			sequences.second = cliArguments.find(CliParser::halfTwoKey)->second;
		}
		return make_pair(sequenceParser.getSequenceFromString(sequences.first), sequenceParser.getSequenceFromString(sequences.second));
}

int main(int argc, const char* argv[])
{
		signal(SIGINT, signalHandler);
		signal(SIGTERM, signalHandler);
		map<string, string> cliArguments = getCliArguments(argc, argv);
		string configPath = getConfigFilePath(cliArguments);
		ConfigParser configParser(configPath);
		pair<list<SequenceItem>, list<SequenceItem>> sequencePair = getSequences(configParser, cliArguments);
		cout << "config path =====> " << configPath << endl;
		map<string, string> configs = configParser.getConfigs();

		SequenceRunner sequenceRunner(sequencePair, configs[ConfigParser::pinKeyHalfOne], configs[ConfigParser::pinKeyHalfTwo]);
		sequenceRunner.run();
		return 0;
}

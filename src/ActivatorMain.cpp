#include "SequenceParser.h"
#include "ConfigParser.h"
#include "CliParser.h"
#include "SequenceRunner.h"
#include "Utility.h"
#include "Logger.h"
#include "ErrorCodeException.h"
#include "version.h"

#include <string>
#include <iostream>
#include <utility>
#include <csignal>


using namespace std;

#define DEFAULT_CONFIG_PATH "/opt/cdh_2smard/config.cfg"

void signalHandler(int signal) {
		Logger::info("\n================== EXECUTION INTERRUPTED ==================");
		Logger::info("Received signal = " + to_string(signal));
		Logger::info("2SMARD will be deactivated");
		SequenceRunner::stopRun();
}

pair<list<SequenceItem>, list<SequenceItem>> getSequences(ConfigParser &configParser, const map<string, string> &cliArguments) {
		SequenceParser sequenceParser;
		pair<string, string> sequences = configParser.getSequences();

		if(cliArguments.count(CliParser::halfOneKey) != 0) {
			Logger::info("Override first half with = " + cliArguments.find(CliParser::halfOneKey)->second);
			sequences.first = cliArguments.find(CliParser::halfOneKey)->second;
		}

		if(cliArguments.count(CliParser::halfTwoKey) != 0) {
			Logger::info("Override second half with = " + cliArguments.find(CliParser::halfTwoKey)->second);
			sequences.second = cliArguments.find(CliParser::halfTwoKey)->second;
		}
		return make_pair(sequenceParser.getSequenceFromString(sequences.first), sequenceParser.getSequenceFromString(sequences.second));
}

void run(int argc, const char* argv[]) {
		Logger::info("Starting 2smard activator v." + string(VERSION));
		signal(SIGINT, signalHandler);
		signal(SIGTERM, signalHandler);
		map<string, string> cliArguments = Utility::getCliArguments(argc, argv);
		string configPath = Utility::getConfigFilePath(cliArguments);
		ConfigParser configParser(configPath);
		pair<list<SequenceItem>, list<SequenceItem>> sequencePair = getSequences(configParser, cliArguments);
		map<string, string> configs = configParser.getConfigs();
		SequenceRunner sequenceRunner(sequencePair);
		sequenceRunner.run();
}

int main(int argc, const char* argv[])
{
		try {
			run(argc, argv);
			return 0;
		} catch(ErrorCodeException& exception) {
			Logger::error(exception.getMessage());
			return 1;
		} catch(...) {
			Logger::critical("2SMARD-005 : Unexpected error occured");
			return 1;
		}
}

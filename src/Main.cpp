#include "Config.h"

#include <iostream>

using namespace std;

int main(int argc, const char* argv[])
{
	Config config;
	list<SequenceItem> items = config.getSequenceFromString("A300m|I4000s|123123|123123|123123");
	for(SequenceItem item: items) {
		cout << item.getPeriod() << endl;
	}
	return 0;
}

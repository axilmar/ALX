#include <iostream>
#include "Config.hpp"


using namespace std;
using namespace alx;


int main() {
    Config config, config1;
    ConfigSectionContainer sections = config.getSections();
    for(const char *section : sections) {
        ConfigEntryContainer entries = config.getEntries(section);
        for(const char *entry : entries) {
        }
    }
    config + config1;
    config += config1;
	return 0;
}

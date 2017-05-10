//
//  IDS.cpp
//  A3 IDS
//
//

#include "IDS.hpp"

int main (int argc, char** argv) {
	init();
	return EXIT_SUCCESS;
}

int init() {
	int success = EXIT_SUCCESS;
	
		//if any of these conditions fail
	if (		readEntry(entryFile) == EXIT_FAILURE
		|| 	readStats(statsFile) == EXIT_FAILURE) {
		success = EXIT_FAILURE;
	}
	
	std::cout 	<< "Events\t-> " 	<< events.size() << std::endl;
	std::cout 	<< "Stats\t-> " 		<< stats.size() << std::endl;
	
		//have to use dynamic_cast or it won't work properly.
//	for (std::vector<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
//		if ((*it)->getCD() == 'C') {
//			ContinuousEvent c = *dynamic_cast<ContinuousEvent*>(*(it));
//			std::cout 	<< c.getMax() << std::endl;
//		} else if ((*it)->getCD() == 'D') {
//			DiscreteEvent d = *dynamic_cast<DiscreteEvent*>(*(it));
//			std::cout 	<< d.getWeight() << " - " << d.getMin() << std::endl;
//		}
//	}
	
	return success;
}

int readEntry(std::string filename) {
	int success = EXIT_SUCCESS;
	std::fstream infile (filename.c_str(), std::ios::in);
	
	if (!infile) {
		infile.close();
		std::cout 	<< "Failed to read " << filename << "! Exiting.." << std::endl;
		success = EXIT_FAILURE;
	} else {
		int count;
		infile >> count;
		infile.ignore(256, '\n');
		
		std::string line, delim = ":";
		while (std::getline(infile, line) ) {
			std::vector<std::string> tokens = tokenize(line, delim);
			std::string eventName = tokens[0];
			
			if (tokens[1] == "D") {
				char CD = 'D';
				int min = atoi(tokens[2].c_str()),
					max = atoi(tokens[3].c_str()),
					weight = atoi(tokens[4].c_str());
	
				events.push_back(new DiscreteEvent(eventName, CD, weight, min, max));
			} else if (tokens[1] == "C") {
				char CD = 'C';
				float	min = atof(tokens[2].c_str()),
						max = atof(tokens[3].c_str());
				int 	weight = atoi(tokens[4].c_str());
				
				events.push_back(new ContinuousEvent(eventName, CD, weight, min, max));
			}
		}
	}
	
	return success;
}

int readStats(std::string filename) {
	int success = EXIT_SUCCESS;
	std::fstream infile (filename.c_str(), std::ios::in);
	
	if (!infile) {
		infile.close();
		std::cout 	<< "Failed to read " << filename << "! Exiting.." << std::endl;
		success = EXIT_FAILURE;
	} else {
		int count;
		infile >> count;
		infile.ignore(256, '\n');
		
		std::string line, delim = ":";
		while (std::getline(infile, line) ) {
			std::vector<std::string> tokens = tokenize(line, delim);
			std::string eventName = tokens[0];
			float mean, standardDeviation;
			mean = atof(tokens[1].c_str());
			standardDeviation = atof(tokens[2].c_str());
			
			Stat tempS (eventName, mean, standardDeviation);
			stats.push_back(tempS);
		}
	}
	
	return success;
}

Log generateLogEntry(ContinuousEvent event, Stat stat) {
	std::string eventName = event.getEventName();
	int weight = event.getWeight();
	float value = 5.0;
	
	Log log(eventName, value, weight);
	
	return log;
}












//
//  IDS.cpp
//  Assignment 03
//
//

#include "IDS.hpp"

int main (int argc, char** argv) {
	if (!init()) return EXIT_FAILURE;
	
	return EXIT_SUCCESS;
}

int init() {
		//initialize everything
		//read files, set up stuff, etc.
		//if this fails, return EXIT_FAILURE and quit the program.
	int success = EXIT_SUCCESS;
	
		//if either of these conditions fail, do not continue with the program.
	if (	 readEntry(entryFile) == EXIT_FAILURE || readStats(statsFile) == EXIT_FAILURE )
		success = EXIT_FAILURE;
	
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
			//do something else;
		int count;
		infile >> count;
		infile.ignore(256, '\n');
		
		std::cout 	<< "Count -> " << count << std::endl;
		
		std::string line, delim = ":";
		while (std::getline(infile, line) ) {
				//std::cout 	<< "Line -> " << line << std::endl;
			
			std::vector<std::string> tokens = tokenize(line, delim);
			
			if (tokens[1] == "D") {
				int min = atoi( tokens[2].c_str() );
				int weight = atoi ( tokens[4].c_str() );
				char CD = 'D';
				Entry temp (tokens[0], CD, min, weight);
				events.push_back(temp);
			} else {
				char CD = 'C';
				float min = atof( tokens[2].c_str() );
				float max = atof( tokens[3].c_str() );
				float weight = atof( tokens[4].c_str() );
				Entry temp (tokens[0], CD, min, max, weight);
				events.push_back(temp);
			}
		}
		
		infile.close();
		
		if (count != events.size()) {
			success = EXIT_FAILURE;
			std::cout 	<< "Number of events does not tally with count!" << std::endl
						<< "Number of events:\t" << events.size() << std::endl
						<< "Count provided:\t" << count << std::endl;
		} else {
			std::cout 	<< events.size() << " entries found in " << filename << "!\n" << std::endl;
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
			//do something else;
		int count = 0;
		infile >> count;
		infile.ignore(256, '\n');
		
		std::cout 	<< "Count -> " << count << std::endl;
		
		std::string line, delim = ":";
		while (std::getline(infile, line) ) {
			std::vector<std::string> tokens = tokenize(line, delim);
			
			float mean = atof( tokens[1].c_str() );
			float standardDeviation = atof( tokens[1].c_str() );
			
			Stat temp (tokens[0], mean, standardDeviation);
			stats.push_back(temp);
		}
		
		infile.close();
		
		if (count != stats.size()) {
			success = EXIT_FAILURE;
			std::cout 	<< "Number of statistics does not tally with count!" << std::endl
			<< "Num of stats:\t" << stats.size() << std::endl
			<< "Count provided:\t" << count << std::endl;
		} else {
			std::cout 	<< stats.size() << " stats found in " << filename << "!\n" << std::endl;
		}
	}
	
	return success;
}












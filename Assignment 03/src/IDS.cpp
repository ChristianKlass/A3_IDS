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
	if (	 !readEntry(entryFile) )
		success = EXIT_FAILURE;
	
	return success;
}

int readEntry(std::string filename) {
	int success = EXIT_SUCCESS;
	
	std::fstream infile (filename, std::ios::in);
	
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
				entries.push_back(temp);
			} else {
				char CD = 'C';
				int min = atoi( tokens[2].c_str() );
				int max = atoi( tokens[3].c_str() );
				int weight = atoi ( tokens[4].c_str() );
				Entry temp (tokens[0], CD, min, max, weight);
				entries.push_back(temp);
			}
		}
		
		std::cout	<< entries[1].getEventName() << " - " << entries[1].getMax() << std::endl;
		
		infile.close();
	}
	
	return success;
}













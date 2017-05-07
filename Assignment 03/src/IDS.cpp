//
//  IDS.cpp
//  Assignment 03
//
//  Created by Mark Klass on 7/5/17.
//  Copyright © 2017 Juicy Apps. All rights reserved.
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
	
	if (		!readEntry(entryFile) ) success = EXIT_FAILURE;
	
	
	return success;
}

int readEntry(std::string filename) {
	int success = EXIT_SUCCESS;
	
	std::fstream infile (filename, std::ios::in);
	
	if (!infile) {
		infile.close();
		success = EXIT_FAILURE;
	} else {
			//do something else;
	}
	
	return success;
}

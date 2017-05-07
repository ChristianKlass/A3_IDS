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
	
		//if either of these conditions fail, do not continue with the program.
	if (	 !readEntry(entryFile) || !readStats(statsFile) )
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
		std::string line;
		while (infile >> line) {
			
		}
		
		infile.close();
	}
	
	return success;
}

int readStats(std::string filename) {
	int success = EXIT_SUCCESS;
	
	std::fstream infile (filename, std::ios::in);
	
	if (!infile) {
		infile.close();
		std::cout 	<< "Failed to read " << filename << "! Exiting.." << std::endl;
		success = EXIT_FAILURE;
	} else {
			//do something else;
		std::string line;
		while (infile >> line) {
			
		}
		
		infile.close();
	}
	
	return success;
}













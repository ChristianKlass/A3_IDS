//
//  IDS.hpp
//  Assignment 03
//
//  Created by Mark Klass on 7/5/17.
//  Copyright © 2017 Juicy Apps. All rights reserved.
//

#ifndef IDS_hpp
#define IDS_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Entry.hpp"
#include "Stat.hpp"

int init();
int readEntry(std::string);
int readStats(std::string);

std::vector<Entry> entries;
std::vector<Stat> stats;

std::string entryFile = "Entry.txt";
std::string statsFile = "Stats.txt";

template<typename T>
std::vector<T> tokenize(const T & str, const T & delimiter) {
	std::vector<T> tokens;
	
	int i = 0;
	int pos = str.find(delimiter);
	while (pos != std::string::npos) {
		tokens.push_back(str.substr(i, pos-i));
		
		i = ++pos;
		pos = str.find(delimiter, pos);
		
		if (pos == std::string::npos)
		tokens.push_back(str.substr(i, str.length()));
	}
	
	return tokens;
}

#endif /* IDS_hpp */

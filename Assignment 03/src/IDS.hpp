//
//  IDS.hpp
//  A3 IDS
//
//

#ifndef IDS_hpp
#define IDS_hpp

#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include "Event.hpp"
#include "ContinuousEvent.hpp"
#include "DiscreteEvent.hpp"
#include "Stat.hpp"
#include "Log.hpp"

int init();
int readEntry(std::string);
int readStats(std::string);
void generateLogEntry(Event*, Stat*, std::vector<Log*>&);
bool withinStatisticC(float, double, double);
bool withinStatisticD(int, int, int);
double generateValue(double, double);

std::vector<Event*> events;
std::vector<Stat*> stats;
std::vector< std::vector<Log*> > logSheet;

	//keep track of the daily totals
	//helps in calculating mean, variance, and SD
std::vector<int> 	dailyLoginCount;
std::vector<int> 	dailyEmailsSent;
std::vector<int> 	dailyEmailsRecv;
std::vector<float> 	dailyTimeOnline;

float findMean(std::vector<int>);
float findMean(std::vector<float>);

float findVariance(std::vector<int>, float);
float findVariance(std::vector<float>, float);

void readLogs(std::string);
void compareStats(std::string);

std::string entryFile = "Events.txt";
std::string statsFile = "Stats.txt";
std::string logFile = "Daily.log";
	//chose to have a SINGLE log file that will detail the information from ALL days.

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

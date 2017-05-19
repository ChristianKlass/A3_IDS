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
int readEvents(std::string);
int readStats(std::string);
void generateLogEntry(Event*, Stat*, std::vector<Log*>&);
bool withinStatisticC(float, double, double);
bool withinStatisticD(int, int, int);
double generateValue(double, double);
void writeLogFile(int);
double findMean(std::vector<double>);
double findVariance(std::vector<double>, double);
void readLogs(std::string);
void compareStats(std::string);
void writeStats (std::vector<double>, std::vector<double>);
void generateLogs(int);
int generateLiveData();

void doAnalysis(std::string dailyFile, std::string newStats);

std::vector<Event*> events;
std::vector<Stat*> stats; 
std::vector<Log*> logs;
std::vector< std::vector<Log*> > logSheet; //USED FOR STORING MULTIPLE DAILY LOGS
std::vector<std::string> eventNames; //USED FOR READING LOG FILES

//keep track of the daily totals
//helps in calculating mean, variance, and SD
std::vector<int> 	dailyLoginCount;
std::vector<int> 	dailyEmailsSent;
std::vector<int> 	dailyEmailsRecv;
std::vector<float> 	dailyTimeOnline;

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

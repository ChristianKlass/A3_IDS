//
//  Log.hpp
//  Assignment 03
//
//

#ifndef Log_hpp
#define Log_hpp

#include "Entry.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>

class Log{
private:
	std::string eventName;
	float value;
	float weight;
	
public:
	Log();
	Log(std::string eventName, float value, float weight);
	~Log();
	
	std::string getEventName();
	float getValue();
	float getWeight();
	
	void setEventName(std::string);
	void setValue(float);
	void setWeight(float);
};

#endif /* Log_hpp */
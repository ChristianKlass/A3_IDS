	//
	//  Log.hpp
	//  Assignment 03
	//
	//

#ifndef Log_hpp
#define Log_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Log {
private:
	std::string eventName;
	float value;
	int weight;
	
public:
	Log();
	Log(std::string eventName, float value, int weight);
	Log(std::string eventName, int value, int weight);
	~Log();
	
	std::string getEventName();
	float getValue();
	int getWeight();
	
	void setEventName(std::string);
	void setValue(float);
	void setWeight(int);
};

#endif /* Log_hpp */

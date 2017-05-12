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
	char CD;
	int weight;
	
public:
	Log();
	Log(std::string eventName, char cd, double value, int weight);
	//Log(std::string eventName, char cd, double value, int weight);
	~Log();
	
	std::string getEventName();
	float getValue();
	int getWeight();
	char getCD();
	
	void setEventName(std::string);
	void setValue(float);
	void setWeight(int);
	void setCD(char);
};

#endif /* Log_hpp */

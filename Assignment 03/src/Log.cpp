	//
	//  Log.cpp
	//  Assignment 03
	//
	//

#include "Log.hpp"

Log::Log() {};

/*Log::Log(std::string eventName, char cd, double value, int weight){
	setEventName(eventName);
	setCD(cd);
	setValue(value);
	setWeight(weight);
}*/

Log::Log(std::string eventName, char cd, int weight){
	setEventName(eventName);
	setCD(cd);
	setWeight(weight);
}

/*Log::Log(std::string eventName, char cd, double value, int weight){
	setEventName(eventName);
	setCD(cd);
	float v = value * 1.0;
	setValue(v);
	setWeight(weight);
}*/

Log::~Log() {}

void Log::setEventName(std::string eventName){
	this->eventName = eventName;
}

void Log::setValue(int index, double value){
	this->values.push_back(value);
}

void Log::setWeight(int weight){
	this->weight = weight;
}

void Log::setCD(char CD){
	this->CD = CD;
}

std::string Log::getEventName(){
	return this->eventName;
}

double Log::getValue(int day){
	return this->values[day-1];
}

int Log::getWeight(){
	return this->weight;
}

char Log::getCD(){
	return this->CD;
}

int Log::getDays(){
	return this->values.size();
}

std::vector<double> Log::getVector(){
	return this->values;
}

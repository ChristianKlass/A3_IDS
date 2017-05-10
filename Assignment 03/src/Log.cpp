	//
	//  Log.cpp
	//  Assignment 03
	//
	//

#include "Log.hpp"

Log::Log() {};

Log::Log(std::string eventName, float value, int weight){
	setEventName(eventName);
	setValue(value);
	setWeight(weight);
}

Log::Log(std::string eventName, int value, int weight){
	setEventName(eventName);
	float v = value * 1.0;
	setValue(v);
	setWeight(weight);
}

Log::~Log() {}

void Log::setEventName(std::string eventName){
	this->eventName = eventName;
}

void Log::setValue(float value){
	this->value = value;
}

void Log::setWeight(int weight){
	this->weight = weight;
}

std::string Log::getEventName(){
	return this->eventName;
}

float Log::getValue(){
	return this->value;
}

int Log::getWeight(){
	return this->weight;
}

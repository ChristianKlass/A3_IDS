//
//  Log.cpp
//  Assignment 03
//
//

#include "Log.hpp"

Log::Log() {};

Log::Log(std::string eventName, float value, float weight){
	setEventName(eventName);
	setValue(value);
	setWeight(weight);
}

Log::Log(std::string eventName, int value, int weight){
	setEventName(eventName);
	
	float v = value * 1.0;
	float w = weight * 1.0;
	setValue(v);
	setWeight(w);
}

Log::~Log() {}

void Log::setEventName(std::string eventName){
	this->eventName = eventName;
}

void Log::setValue(float value){
	this->value = value;
}

void Log::setWeight(float weight){
	this->weight = weight;
}

std::string Log::getEventName(){
	return this->eventName;
}

float Log::getValue(){
	return this->value;
}

float Log::getWeight(){
	return this->weight;
}

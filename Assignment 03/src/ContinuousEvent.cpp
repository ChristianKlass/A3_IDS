//
//  ContinuousEvent.cpp
//  A3 IDS
//
//

#include "ContinuousEvent.hpp"

ContinuousEvent::ContinuousEvent() {}
ContinuousEvent::~ContinuousEvent() {}
ContinuousEvent::ContinuousEvent(std::string eventName, char CD, int weight, float min, float max): Event(eventName, CD, weight) {
	setMin(min);
	setMax(max);
}

void ContinuousEvent::setMin(float min) {
	this->min = min;
}

void ContinuousEvent::setMax(float max) {
	this->max = max;
}

float ContinuousEvent::getMin() {
	return this->min;
}

float ContinuousEvent::getMax() {
	return this->max;
}

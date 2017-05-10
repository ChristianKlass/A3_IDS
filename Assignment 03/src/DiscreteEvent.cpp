//
//  DiscreteEvent.cpp
//  A3 IDS
//
//  Created by Mark Klass on 10/5/17.
//  Copyright © 2017 Juicy Apps. All rights reserved.
//

#include "DiscreteEvent.hpp"

DiscreteEvent::DiscreteEvent() {}
DiscreteEvent::~DiscreteEvent() {}
DiscreteEvent::DiscreteEvent(std::string eventName, char CD, int weight, int min, int max): Event(eventName, CD, weight) {
	setMin(min);
	setMax(max);
}

void DiscreteEvent::setMin(int min) {
	this->min = min;
}

void DiscreteEvent::setMax(int max) {
	this->max = max;
}

int DiscreteEvent::getMin() {
	return this->min;
}

int DiscreteEvent::getMax() {
	return this->max;
}

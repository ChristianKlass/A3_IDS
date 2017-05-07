//
//  Stat.cpp
//  Assignment 03
//
//  Created by Mark Klass on 7/5/17.
//  Copyright © 2017 Juicy Apps. All rights reserved.
//

#include "Stat.hpp"

Stat::Stat() {}
Stat::Stat(std::string eventName, float mean, float standardDeviation) {
	
}

void Stat::setEventName(std::string eventName) {
	this->eventName = eventName;
}

void Stat::setMean(float mean) {
	this->mean = mean;
}

void Stat::setStandardDeviation(float standardDeviation) {
	this->standardDeviation = standardDeviation;
}

float Stat::getMean() { return this->mean; }
float Stat::getStandardDeviation() { return this->standardDeviation; }
std::string Stat::getEventName() { return this->eventName; }

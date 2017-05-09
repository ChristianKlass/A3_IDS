//
//  Entry.cpp
//  Assignment 03
//
//

#include "Entry.hpp"

Entry::Entry() {};
Entry::Entry(std::string eventName, char CD, float min, float max, float weight) {
	setEventName(eventName);
	setCD(CD);
	setMin(min);
	setMax(max);
	setWeight(weight);
}

Entry::Entry(std::string eventName, char CD, int min, int weight) {
	setEventName(eventName);
	setCD(CD);
	setMin(min);
	setWeight(weight);
}

Entry::~Entry() {}

void Entry::setEventName (std::string eName) { this->eventName = eName;  }
void Entry::setMin (int min) { this->min = min; }
void Entry::setMax (int max) { this->max = max; }
void Entry::setWeight (int weight) {
	if (weight < 1) {
		std::cout 	<< "Weight cannot be less than 1!\n";
		std::cout 	<< "Defaulting to 1.\n";
		
		weight = 1;
	}
	
	this->weight = weight;
}

void Entry::setMin (float min) { this->min = min; }
void Entry::setMax (float max) { this->max = max; }
void Entry::setWeight (float weight) {
	if (weight < 0.01) {
		std::cout 	<< "Weight cannot be less than 1!\n";
		std::cout 	<< "Defaulting to 1.\n";
		
		weight = 0.01;
	}
	
	this->weight = weight;
}

void Entry::setCD (char CD) 	{
		//in case the entry is lowercase
	if (CD == 'c' || CD == 'd') {
		CD = toupper(CD);
	}
	
		//lazy to implement a selection, so assume D by default
	if (CD != 'C' && CD != 'D') {
		std::cout 	<< "Invalid CD!  CD was " << CD << "!\n";
		std::cout 	<< "Defaulting to 'D'.\n";
		CD = 'D';
	}
	
	this->CD = CD;
}

std::string Entry::getEventName() { return this->eventName; }
int Entry::getMin() { return this->min; };
int Entry::getMax() { return this->max; };
int Entry::getWeight() { return this->weight; };

float Entry::getFMin() { return this->fMin; }
float Entry::getFMax() { return this->fMax; }
float Entry::getFWeight() { return this->fWeight; }

std::string Entry::getCD() {
	std::string answer;
	
	if (CD == 'C') {
		answer = "Continuous";
	} else {
		answer = "Discrete";
	}
	
	return answer;
}

std::string Entry::toString() {
	std::stringstream ss;
	ss << this->getEventName() << " - " << this->getWeight();
	
	return ss.str();
}



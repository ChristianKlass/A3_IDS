//
//  Stat.hpp
//  Assignment 03
//
//  Created by Mark Klass on 7/5/17.
//  Copyright © 2017 Juicy Apps. All rights reserved.
//

#ifndef Stat_hpp
#define Stat_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

class Stat {
private:
	std::string eventName;
	float mean;
	float standardDeviation;
	
public:
	Stat();
	Stat(std::string eventName, float mean, float standardDeviation);
	
	std::string getEventName();
	float getMean();
	float getStandardDeviation();
	
	void setEventName(std::string);
	void setMean(float);
	void setStandardDeviation(float);
};

#endif /* Stat_hpp */

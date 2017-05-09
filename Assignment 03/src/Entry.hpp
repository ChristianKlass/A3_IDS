//
//  Entry.hpp
//  Assignment 03
//
//

#ifndef Entry_hpp
#define Entry_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Entry {
private:
	std::string eventName;
	char CD; //continuous (C) || discrete (D) <- only these two values are allowed.
	int min, max, weight;
	
public:
	Entry();
		//for C
	Entry(std::string eventName, char CD, int min, int max, int weight);
		//for D
	Entry(std::string eventName, char CD, int min, int weight);
	~Entry();
	
		//accessors and mutators
	void setEventName(std::string);
	void setCD (char);
	void setMin(int);
	void setMax(int);
	void setWeight(int);
	
	std::string getEventName();
	std::string getCD();
	int getMin();
	int getMax();
	int getWeight();
		//accessors and mutators
};

#endif /* Entry_hpp */

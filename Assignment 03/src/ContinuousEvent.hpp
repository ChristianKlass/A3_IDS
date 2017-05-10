//
//  ContinuousEvent.hpp
//  A3 IDS
//
//

#ifndef ContinuousEvent_hpp
#define ContinuousEvent_hpp

#include <stdio.h>
#include "Event.hpp"

class ContinuousEvent: public Event {
private:
	float min, max;
	
public:
	ContinuousEvent();
	ContinuousEvent(std::string eventName, char CD, int weight, float min, float max);
	
	~ContinuousEvent();
	
	void setMin (float);
	void setMax (float);
	
	virtual float getMin();
	float getMax();
};

#endif /* ContinuousEvent_hpp */

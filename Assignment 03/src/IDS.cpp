//
//  IDS.cpp
//  A3 IDS
//
//

#include "IDS.hpp"

int main (int argc, char** argv) {
	init();

	srand((int)time(NULL));

	int numberOfLogs = 5;

	//DAILY LOG GENERATION //5 DAYS FOR NOW
	//NEED TO UPDATE DEPENDING ON USER INPUT
	std::cout << "Generating " << numberOfLogs << " daily logs for event..." << std::endl;
	std::cout << "##########################################################" << std::endl << std::endl;
	for(int days = 0; days < numberOfLogs; days++){
		//Vector of <Vectors of log> acting as logsheet
		std::vector<Log*> dailyLog;
		for (int i = 0; i < events.size(); i++) {
			generateLogEntry(events[i], stats[i], dailyLog);
		}
		logSheet.push_back(dailyLog);
	}//END DAILY LOG GENERATION

	//READING OF LOGSHEET
	std::string logFile = "Daily.log";
	std::fstream outFile(logFile.c_str(), std::ios::out);
	
	if (!outFile) {
		outFile.close();
		std::cout << "\n*****" << logFile << " failed to open for data writing*****" << std::endl;
	} else {
		for (int days = 0; days < logSheet.size(); ++days) {
			outFile << "~~~ Day " << days + 1 << "~~~" << std::endl;
			std::stringstream data;
			data.str("");
			
				//FOR LOOP TO EXTRACT DAILY EVENTS FROM LOGSHEET
			for(int i = 0; i < logSheet[days].size(); i++){
				data << logSheet[days][i]->getEventName() << ":";
				data << logSheet[days][i]->getCD() << ":";
				
				if ( logSheet[days][i]->getCD() == 'C' ) {
					std::cout 	<< "Pres\n";
					data << std::setprecision(2) << std::fixed << logSheet[days][i]->getValue() << ":";
				} else {
					data << std::setprecision(0) << std::fixed << logSheet[days][i]->getValue() << ":";
				}
			
				data << logSheet[days][i]->getWeight() << ":" << std::endl;
			}
			
			outFile << data.str().c_str();
		}
		
		outFile.close();
	}
	return EXIT_SUCCESS;
}

int init() {
	int success = EXIT_SUCCESS;

		//if any of these conditions fail
	if (	readEntry(entryFile) == EXIT_FAILURE || readStats(statsFile) == EXIT_FAILURE) {
		success = EXIT_FAILURE;
	}

	std::cout << "\n\nTotal number of Events read\t-> " << events.size() << std::endl;
	std::cout << "Statisical data of Events read\t-> " << stats.size() << std::endl;

	return success;
}

int readEntry(std::string filename) {
	int success = EXIT_SUCCESS;
	std::fstream infile (filename.c_str(), std::ios::in);

	if (!infile) {
		infile.close();
		std::cout 	<< "Failed to read " << filename << "! Exiting.." << std::endl;
		success = EXIT_FAILURE;
	} else {
		int count;
		infile >> count;
		infile.ignore(256, '\n');

		std::string line, delim = ":";
		while (std::getline(infile, line) ) {
			std::vector<std::string> tokens = tokenize(line, delim);
			std::string eventName = tokens[0];

			if (tokens[1] == "D") {
				char CD = 'D';
				int min, max, weight;
				/*int min = atoi(tokens[2].c_str());
				max = atoi(tokens[3].c_str()),
				weight = atoi(tokens[4].c_str());*/
				min = atoi(tokens[2].c_str());
				if(tokens[3] == ""){
					max = 9999;
				}
				else{
					max = atoi(tokens[3].c_str());
				}
				weight = atoi(tokens[4].c_str());
				std::cout << "MAX " << max << std::endl;//TEST
//				std::cout 	<< "STORE D!\n";
				events.push_back(new DiscreteEvent(eventName, CD, weight, min, max));
			} else if (tokens[1] == "C") {
				char CD = 'C';
				float min, max;
				int weight;

				/*float	min = atof(tokens[2].c_str()),
				max = atof(tokens[3].c_str());
				int 	weight = atoi(tokens[4].c_str());*/
				min = atoi(tokens[2].c_str());
				if(tokens[3] == ""){
					max = 9999.99;
				}
				else{
					max = atof(tokens[3].c_str());
				}
				weight = atoi(tokens[4].c_str());
				
//				std::cout 	<< "STORE C!\n";
				events.push_back(new ContinuousEvent(eventName, CD, weight, min, max));
			}
		}
	}

	return success;
}

int readStats(std::string filename) {
	int success = EXIT_SUCCESS;
	std::fstream infile (filename.c_str(), std::ios::in);

	if (!infile) {
		infile.close();
		std::cout 	<< "Failed to read " << filename << "! Exiting.." << std::endl;
		success = EXIT_FAILURE;
	} else {
		int count;
		infile >> count;
		infile.ignore(256, '\n');

		std::string line, delim = ":";
		while (std::getline(infile, line) ) {
			std::vector<std::string> tokens = tokenize(line, delim);
			std::string eventName = tokens[0];
			float mean, standardDeviation;
			mean = atof(tokens[1].c_str());
			standardDeviation = atof(tokens[2].c_str());

			//Stat tempS (eventName, mean, standardDeviation);
			//stats.push_back(tempS);

			//TEST
			stats.push_back(new Stat(eventName, mean, standardDeviation)); 
		}
	}

	return success;
}

void generateLogEntry(Event* event, Stat* stat, std::vector<Log*> &dailyLog) {

	//std::cout << "In generateLog function" << std::endl;//TEST
	std::string eventName = event->getEventName();
	int weight = event->getWeight();

	if(event->getCD() == 'C'){
		double value;
		ContinuousEvent cEvent = *dynamic_cast<ContinuousEvent*>(event);

		//std::cout << "MIN - " << cEvent.getMin() << "MAX - " << cEvent.getMax() << std::endl;//TEST

		do{
			//Problem here, min and max can be zero and therefore DIV/0
			//Set the value to 1 instead so that it makes sense
			if(cEvent.getMin() == 0 && cEvent.getMax() == 0){
				value = 1;
				break;
			}
			else{
				value = generateValue(stat->getMean(), stat->getStandardDeviation());
				std::cout << "C VALUE -> " << value << std::endl;//TEST
			}

		}while(withinStatisticC(value, cEvent.getMin(), cEvent.getMax()) == false);

		//return (new Log(eventName, value, weight));
		dailyLog.push_back(new Log(eventName, event->getCD(), value, weight));
		//std::cout << dailyLog.size() << std::endl;

		//std::cout << value << std::endl; //TEST
	}
	
	if(event->getCD() == 'D'){
		double value;
		DiscreteEvent dEvent = *dynamic_cast<DiscreteEvent*>(event);

		//std::cout << "MIN - " << dEvent.getMin() << "MAX - " << dEvent.getMax() << std::endl;//TEST
		do{
			//Problem here, min and max can be zero and therefore DIV/0
			//Set the value to 1 instead so that it makes sense
			/*if(dEvent.getMin() == 0 && dEvent.getMax() == 0){
				value = 1;
				break;
			}
			else{
				value = generateValue(stat->getMean(), stat->getStandardDeviation());
				value = (int) value;
				//std::cout << "D VALUE -> " << value << std::endl;//TEST
			}*/
			value = generateValue(stat->getMean(), stat->getStandardDeviation());
			value = (int) value;
			std::cout << "D VALUE -> " << value << std::endl;//TEST
			std::cout << "MIN " << dEvent.getMin() << " MAX " << dEvent.getMax() << std::endl;

		}while(withinStatisticD(value, dEvent.getMin(), dEvent.getMax()) == false);

		//return (new Log(eventName, value, weight));
		dailyLog.push_back(new Log(eventName, event->getCD(), value, weight));
	}

	//Log tempL(eventName, value, weight);
	//logs.push_back(new Log(eventName, value, weight));


}

bool withinStatisticD(int value, int min, int max){
	//If value is greater than mean-SD and value is smaller than mean+SD
	if(value >= min && value <= max){
			//std::cout << "OK" << std::endl;//TEST
		std::cout 	<< "withinStatisticD\n";
		return true;
	}
	
	else
		return false;
}

bool withinStatisticC(float value, double min, double max){
	//If value is greater than mean-SD and value is smaller than mean+SD
	if(value >= min && value <= max){
			//std::cout << "OK" << std::endl;//TEST
		std::cout 	<< "withinStatisticC\n";
		return true;
	}

	else
		return false;
}

double generateValue(double mean, double stdDev){

	bool hasSpare = false;
	double spare = 0.0;

	if(hasSpare)
	{
		hasSpare = false;
		return mean + stdDev * spare;
	}

	hasSpare = true;
	static double u, v, s;
	do
	{
		u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
		v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
		s = u * u + v * v;
	}
	while( (s >= 1.0) || (s == 0.0) );

	s = sqrt(-2.0 * log(s) / s);
	spare = v * s;

	return mean + stdDev * u * s;
}

float findMean(std::vector<int> numbers) {
	float total = 0;
	int count = 0;
	for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
		total += *it;
		
		++count;
	}
	
	total = total / count;
	return total;
}

float findVariance (std::vector<int> numbers, float mean) {
	float variance = 0.0;
	int count = 0;
	
	for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
		float temp = *it - mean;
		
		if (temp > 0) {
			std::cout 	<< "(" << temp << ")^2 = ";
			temp = (temp * temp);
			std::cout 	<< temp << std::endl;
			variance += temp;
		}
		
		++count;
	}
	variance *= 2;
	variance = variance / count;
	
	return variance;
}

/*
void readLogs(std::vector < std::vector<Log*> > readLogs){
	
}

Stat generateNewStat(std::vector < std::vector<Log*> > logSheet){

}*/

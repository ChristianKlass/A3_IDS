//
//  IDS.cpp
//  A3 IDS
//
//

#include "IDS.hpp"

	//The command to run the program -> the last arg is the NAME of the employee you want to generate the Stat file for.
	//IDS Event.txt Stat.txt 100 Sionggo
int main (int argc, char** argv) {
	if (argc == 4 || argc == 5) {
		eventFile = argv[1];
		statsFile = argv[2];
		noOfDays = atoi(argv[3]);
		
		if (argc == 5) {
				//defaults to peter
			username = argv[4];
		}
	} else if (argc != 1) {
		std::cout 	<< "Invalid number of arguments!\n";
		exit (-1);
	} else {
		std::cout 	<< "Using defaults.\n";
	}
	
	init();

	// ~~~ LEARNING PHASE ~~~ 
	srand((int)time(NULL));
	
	generateLogs(noOfDays);

	writeLogFile(noOfDays, logFile);

	//newStatsFile will be generated in this function too.
	readLogs(logFile);

	// ~~~  ANALYSIS PHASE ~~~
	std::string dFile = "Whatever.txt";
	std::string stats = "newStats.txt";
	doAnalysis (dFile, stats);

		//int a = generateLiveData();
	
	compareLogs("Daily.log", stats);

		//std::cout << "HERE" << a << std::endl;

	return EXIT_SUCCESS;
}

int init() {
	std::cout << "\n\n\n####################################################################" << std::endl;

	int success = EXIT_SUCCESS;

	//IF ANY OF THE CONDITIONS FAILED
	if (	readEvents(eventFile) == EXIT_FAILURE || readStats(statsFile) == EXIT_FAILURE) {
		success = EXIT_FAILURE;
	}

	std::cout << "\nTotal number of Events read \t\t -> " << events.size() << std::endl;
	std::cout << "Number of events in statistical data \t -> " << stats.size() << std::endl;
	return success;
}

int readEvents(std::string filename) {
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
			eventNames.push_back(eventName);

			if (tokens[1] == "D") {
				char CD = 'D';
				int min, max, weight;
				
				min = atoi(tokens[2].c_str());
				if(tokens[3] == ""){
					max = 9999;
				}
				else{
					max = atoi(tokens[3].c_str());
				}
				weight = atoi(tokens[4].c_str());
				events.push_back(new DiscreteEvent(eventName, CD, weight, min, max));
				
			} else if (tokens[1] == "C") {
				char CD = 'C';
				float min, max;
				int weight;
				
				min = atoi(tokens[2].c_str());
				if(tokens[3] == ""){
					max = 9999.99;
				}
				else{
					max = atof(tokens[3].c_str());
				}
				weight = atoi(tokens[4].c_str());
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

			//TEST
			stats.push_back(new Stat(eventName, mean, standardDeviation)); 
		}
	}

	return success;
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

double findMean(std::vector<double> numbers) {
	float total = 0;
	int count = 0;
	for (std::vector<double>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
		total += *it;
		
		++count;
	}
	
	total = total / count;
	return total;
}

double findVariance (std::vector<double> numbers, double mean) {
	double variance = 0.0;
	int count = 0;
	
	for (std::vector<double>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
		double temp = *it - mean;
		
		if (temp > 0) {
			temp = (temp * temp);
			variance += temp;
		}
		
		++count;
	}
	variance *= 2;
	variance = variance / count;
	
	return variance;
}

//void compareStats() {
//	std::string newStatsFile;
//	std::cout 	<< "Please enter name of new Stats file: ";
//	std::getline(std::cin, newStatsFile);
//	
//	std::fstream infile (newStatsFile.c_str(), std::ios::in);
//	if (!infile) {
//		std::cout 	<< "Could not find " << newStatsFile << "! Please try again!\n";
//		infile.close();
//	} else {
//		int count;
//		std::string eventName;
//		float mean = 0.0, standardDeviation = 0.0, anomalyCount = 0.0;
//		infile >> count;
//		infile.ignore(256, '\n');
//		
//		std::string line, delim = ":";
//		
//			//reads the new stats file
//		while (std::getline(infile, line) ) {
//			std::vector<std::string> tokens = tokenize(line, delim);
//			eventName = tokens[0];
//			mean = atof(tokens[1].c_str());
//			standardDeviation = atof(tokens[2].c_str());
//			
//		}
//	}
//}

void writeLogFile(int noOfDays, std::string filename){
	std::cout << "\n\n\n####################################################################" << std::endl;
	std::cout << "\nBegin writing to log file" << std::endl;
	std::fstream outFile(logFile.c_str(), std::ios::out);
	
	if (!outFile) {
		outFile.close();
		std::cout << "\n*****" << filename << " failed to open for data writing*****" << std::endl;
	} else {
		
		//FOR LOOP TO EXTRACT DAILY EVENTS FROM LOGSHEET
		for(int k = 0; k < noOfDays; k++){
			std::stringstream data;
			outFile << "~~~ Day " << k + 1 << " ~~~" << std::endl;
			for (int i = 0; i < events.size(); ++i) {
				data.str("");
				data << logs[i]->getEventName() << ":";
				data << logs[i]->getCD() << ":";
				
				if ( logs[i]->getCD() == 'C' ) {
					data << std::setprecision(2) << std::fixed << logs[i]->getValue(k) << ":";
				} else {
					data << std::setprecision(0) << std::fixed << logs[i]->getValue(k) << ":";
				}

				data << logs[i]->getWeight() << ":" << std::endl;

				outFile << data.str().c_str();
			}
		}
		
		outFile.close();
	}
}

void generateLogs(int numberOfLogs) {
	//TEST MAKING LOGS
	//LOOP ACCORDING TO NUMBER OF EVENTS
	//std::cout << events.size() << std::endl;
	for(int i = 0; i < events.size(); i++){
		//PUSH EVENTS INTO VECTOR OF LOGS
		logs.push_back(new Log(events[i]->getEventName(), events[i]->getCD(), events[i]->getWeight()));

		//GENERATE VALUES FOR EVENTS ACCORDING TO NUMBER OF DAYS
		for(int k = 0; k < numberOfLogs; k++){

			if(events[i]->getCD() == 'C'){
				ContinuousEvent cEvent = *dynamic_cast<ContinuousEvent*>(events[i]);
				double value;
				do{
					value = generateValue(stats[i]->getMean(), stats[i]->getStandardDeviation());
				}while(withinStatisticC(value, cEvent.getMin(), cEvent.getMax()) == false);
				
				logs[i]->setValue(k, value);
			}

			if(events[i]->getCD() == 'D'){
				DiscreteEvent dEvent = *dynamic_cast<DiscreteEvent*>(events[i]);
				double value;
				do{
					value = generateValue(stats[i]->getMean(), stats[i]->getStandardDeviation());
				}while(withinStatisticC(value, dEvent.getMin(), dEvent.getMax()) == false);
				
				logs[i]->setValue(k, value);
			}
		}
		
	}
}

void writeStats (std::vector<double> mean, std::vector<double> stdDiv) {
	std::stringstream output;
	std::string filename = "newStats.txt";
	std::fstream outfile(filename.c_str(), std::ios::out);

	if (!outfile) {
		std::cout 	<< "FAIL!\n";
		outfile.close();
	} else {
		outfile << events.size() << std::endl;

		for (int i = 0; i < events.size(); ++i) {
			output.str("");

			if ( logs[i]->getCD() == 'C' ) {
				output 	<< events[i]->getEventName() << ":" 
				<< std::setprecision(2) << std::fixed 
				<< mean[i] << ":" 
				<< std::setprecision(2) << std::fixed 
				<< stdDiv[i] << ":";
			} else {
				output 	<< events[i]->getEventName() << ":" 
				<< std::setprecision(0) << std::fixed 
				<< mean[i] << ":" 
				<< std::setprecision(0) << std::fixed 
				<< stdDiv[i] << ":";
			}

		//	std::cout 	<< output.str() << std::endl;
			outfile << output.str() << std::endl;
		}

		outfile.close();
	}
}

void readLogs(std::string filename) {
	std::cout << "\n\n\n####################################################################" << std::endl;
	std::cout << "\nBegin reading of " << filename << std::endl;
	std::cout << "Number of events read \t-> " << eventNames.size() << std::endl << std::endl;
	for(int i = 0; i < events.size(); i++){
		std::cout << "\t->" << eventNames[i] << std::endl;
	}

	std::cout << std::endl;

	std::fstream infile (filename.c_str(), std::ios::in);

	if (!infile) {
		std::cout 	<< "Could not open " << filename << "! Please make sure it exists!\n";
		infile.close();
	} else {
		std::string line, delim = ":";
		std::stringstream ss ("");
		int day = 1;

			//store the total login, eSent, eReceived, timeOnline;
		std::vector<double> means (events.size(), 0.0), stdDivs (events.size(), 0.0);

		ss << "~~~ Day " << day << " ~~~";
		while (std::getline(infile, line)) {
			if (line == ss.str()) {
				std::cout 	<< "Processing information for day " << day++ << "!\n";
				ss.str("");

				ss << "~~~ Day " << day << " ~~~";
			} else {
				std::vector<std::string> tokens = tokenize(line, delim);
				std::string eventName = tokens[0];
				tokens.pop_back(); 	//POP BACK BECAUSE LAST ELEMENT IS BLANK

				for (int i = 0, n = (int)logs.size(); i < n; ++i) {
					if (logs[i]->getEventName() == eventName) {
						std::vector<double> totals = logs[i]->getVector();
						means[i] = findMean(totals);
						stdDivs[i] = sqrt(findVariance(totals, means[i]));
						break;
					}
				}
			}
		}

		writeStats(means, stdDivs);

		infile.close();
	}
}

void doAnalysis(std::string dailyFile, std::string statsFile) {
	std::string line, delim = ":";
	std::vector <std::vector <std::string> > input, stats;
	double totalWeight = 0;
	double daysWeight = 0;
	double threshold;

	//calculate totalWeight
	for (int i = 0; i < events.size(); ++i) {
		totalWeight += events[i]->getWeight();
	}

	//set threshold
	threshold = 2 * totalWeight;

	//read stats figures
	std::fstream sFile (statsFile.c_str(), std::ios::in);
	if (!sFile) {
		std::cout 	<< "COULD NOT FIND " << statsFile << "!" << std::endl;
		sFile.close();
	} else {
		std::string count;
		std::getline(sFile, count);
		while (std::getline(sFile, line)) {
			stats.push_back(tokenize(line, delim));
		}

		sFile.close();
	}
	
	// read daily figures
	std::fstream dFile (dailyFile.c_str(), std::ios::in);
	if (!dFile) {
		std::cout 	<< "COULD NOT FIND " << dailyFile << "!" << std::endl;
		dFile.close();
	} else {
		std::string count;
		std::getline(dFile, count);
		while (std::getline(dFile, line)) {
			input.push_back(tokenize(line, delim));
		}

		dFile.close();
	}

	std::cout 	<< input.size() << " ** " << stats.size() << std::endl;

	//(statsMean - dailyMean) / statsSD
	//files read, now COMPARE
	for (int i = 0, n = (int)input.size(); i < n; ++i) {
		for (int j = 0, o = (int)stats.size(); j < o; ++j) {
			//compare the name
			if (input[i][0] == stats[i][0]) {
				double statsMean, dailyMean, statsSD;

				statsMean = atof(stats[i][1].c_str());
				dailyMean = atof(input[i][1].c_str());
				statsSD = atof(stats[i][2].c_str());
				daysWeight += ((statsMean - dailyMean) / statsSD);
				break;
			}
		}
	}

	if (daysWeight > threshold) {
		std::cout 	<< "INTRUSION MOTHERFUCKER!\n";
	}

	std::cout 	<< "Threshold ->\t" 	<< threshold << std::endl;
	std::cout 	<< "CurrWeight ->\t" 	<< daysWeight << std::endl;
}

bool withinStatisticC(float value, double min, double max){
	//IF VALUE IS GREATER THAN MEAN-SD && VALUE IS SMALLER THAN MEAN+SD
	if(value >= min && value <= max){
		return true;
	}
	else
		return false;
}


bool withinStatisticD(int value, int min, int max){
	//IF VALUE IS GREATER THAN MEAN-SD && VALUE IS SMALLER THAN MEAN+SD
	if(value >= min && value <= max){
		return true;
	}
	else
		return false;
}

int generateLiveData(){
	std::string liveDataFile, noOfDays;
	int days, count;
	std::cout << "Please enter the base stats file for live data: ";
	std::getline(std::cin, liveDataFile);
	std::cin.clear();
	std::cout << "\nPlease enter the number of days of data to be generated: ";
	std::getline(std::cin, noOfDays);
	days = atoi(noOfDays.c_str());
	std::cin.clear();
	int success = EXIT_SUCCESS;
	std::fstream infile (liveDataFile.c_str(), std::ios::in);

	if (!infile) {
		infile.close();
		std::cout 	<< "\nFailed to read " << liveDataFile << "! Exiting.." << std::endl;
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

			//TEST
			liveData.push_back(new Stat(eventName, mean, standardDeviation)); 
		}
	}

	generateLiveLogs(days);

	writeLiveLogFile(days, "liveDataLog.txt");
	return success;
}


void generateLiveLogs(int numberOfLogs) {
	//TEST MAKING LOGS
	//LOOP ACCORDING TO NUMBER OF EVENTS
	//std::cout << events.size() << std::endl;

	std::cout << "\nBegin generation of RANDOM LIVE DATA of " << numberOfLogs << " days!" << std::endl;
	for(int i = 0; i < events.size(); i++){
		//PUSH EVENTS INTO VECTOR OF LOGS
		liveLogs.push_back(new Log(events[i]->getEventName(), events[i]->getCD(), events[i]->getWeight()));

		//GENERATE VALUES FOR EVENTS ACCORDING TO NUMBER OF DAYS
		for(int k = 0; k < numberOfLogs; k++){

			if(events[i]->getCD() == 'C'){
				ContinuousEvent cEvent = *dynamic_cast<ContinuousEvent*>(events[i]);
				double value;
				do{
					value = generateValue(liveData[i]->getMean(), liveData[i]->getStandardDeviation());
				}while(withinStatisticC(value, cEvent.getMin(), cEvent.getMax()) == false);
				
				liveLogs[i]->setValue(k, value);
			}

			if(events[i]->getCD() == 'D'){
				DiscreteEvent dEvent = *dynamic_cast<DiscreteEvent*>(events[i]);
				double value;
				do{
					value = generateValue(liveData[i]->getMean(), liveData[i]->getStandardDeviation());
				}while(withinStatisticC(value, dEvent.getMin(), dEvent.getMax()) == false);
				
				liveLogs[i]->setValue(k, value);
			}
		}
		
	}
}

void writeLiveLogFile(int noOfDays, std::string filename){
	std::cout << "\n\n\n####################################################################" << std::endl;
	std::cout << "\nBegin writing to live data log file" << std::endl;
	std::fstream outFile(filename.c_str(), std::ios::out);
	
	if (!outFile) {
		outFile.close();
		std::cout << "\n*****" << filename << " failed to open for data writing*****" << std::endl;
	} else {
		
		//FOR LOOP TO EXTRACT DAILY EVENTS FROM LOGSHEET
		for(int k = 0; k < noOfDays; k++){
			std::stringstream data;
			outFile << "~~~ Day " << k + 1 << " ~~~" << std::endl;
			for (int i = 0; i < events.size(); ++i) {
				data.str("");
				data << liveLogs[i]->getEventName() << ":";
				data << liveLogs[i]->getCD() << ":";
				
				if ( logs[i]->getCD() == 'C' ) {
					data << std::setprecision(2) << std::fixed << liveLogs[i]->getValue(k) << ":";
				} else {
					data << std::setprecision(0) << std::fixed << liveLogs[i]->getValue(k) << ":";
				}

				data << liveLogs[i]->getWeight() << ":" << std::endl;

				outFile << data.str().c_str();
			}
		}
		
		outFile.close();
	}
}


void compareLogs(std::string logFile, std::string statsFile) {
	std::cout << "\n\n\n####################################################################" << std::endl;
	std::cout << "\nBegin reading of " << logFile << " and " << statsFile << std::endl;

//	for(int i = 0; i < events.size(); i++){
//		std::cout << "\t->" << eventNames[i] << std::endl;
//	}
	
		//read statsFile and populate stats vector
	std::vector <Stat*> newStats;
	std::fstream stats (statsFile.c_str());
	
	if (!stats) {
		std::cout 	<< "Could not open " << logFile << "! Please make sure it exists!\n";
		stats.close();
	} else {
		std::string statLine, delim = ":";
		std::getline(stats, statLine); //read the first number
		
		while (std::getline(stats, statLine)) {
			std::vector<std::string> tokens = tokenize(statLine, delim);
			std::string eventName = tokens[0];
			float mean = atof(tokens[1].c_str()), stdDiv = atof(tokens[2].c_str());
			newStats.push_back(new Stat (eventName, mean, stdDiv));
		}
	}
	
	std::cout << std::endl;
		//read logFile and compare
	std::fstream theLog (logFile.c_str(), std::ios::in);

	if (!theLog) {
		std::cout 	<< "Could not open " << logFile << "! Please make sure it exists!\n";
		theLog.close();
	} else {
		std::string logLine, delim = ":";
		std::stringstream header ("");
		int day = 1;
		std::vector<Log*> dailyLog;
		header << "~~~ Day " << day << " ~~~";
		while (std::getline(theLog, logLine)) {
				//we're reading the first line (the header)
			if (logLine == header.str()) {
				bool anomaly = compareWithStats(dailyLog, newStats);
				
				if (anomaly) {
					std::cout 	<< "Anomaly found at day " << day << "!\n";
				}
				header.str("");
				header << "~~~ Day " << ++day << " ~~~";
				dailyLog.clear();
			} else {
				std::vector<std::string> logTokens = tokenize(logLine, delim);
					//std::string eventName, char cd, int weight
					//Logins:D:0:2:
				std::string lName = logTokens[0];
				int weight = atoi(logTokens[2].c_str());
				char CD;
				if (logTokens[1] == "D") {
					CD = 'D';
				} else {
					CD = 'C';
				}
				
				std::cout 	<< "PUSHING BACK\n";
				dailyLog.push_back(new Log(lName, CD, weight));
			}
		}
		
		theLog.close();
	}
}

bool compareWithStats(std::vector<Log*> dailyLog, std::vector<Stat*> stats) {
	bool ans = false;
	double weight = 0;

	for(int i = 0; i < events.size(); i++){
		std::cout << events[i]->getEventName() << std::endl;
		weight += events[i]->getWeight();
	}

	weight = 2 * weight;

	std::cout << weight << std::endl;
	
	return ans;
}

	//		std::string line, delim = ":";
	//		std::stringstream ss ("");
	//		int day = 1;
	//
	//			//store the total login, eSent, eReceived, timeOnline;
	//		std::vector<double> means (events.size(), 0.0), stdDivs (events.size(), 0.0);
	//
	//		ss << "~~~ Day " << day << " ~~~";
	//		while (std::getline(infile, line)) {
	//			if (line == ss.str()) {
	//				std::cout 	<< "Comparing information for day " << day++ << "!\n";
	//				ss.str("");
	//
	//				ss << "~~~ Day " << day << " ~~~";
	//			} else {
	//				std::vector<std::string> tokens = tokenize(line, delim);
	//				std::string eventName = tokens[0];
	//				tokens.pop_back(); 	//POP BACK BECAUSE LAST ELEMENT IS BLANK
	//
	//					//compare tokens with stats
	//
	//
	//				for (int i = 0, n = (int)logs.size(); i < n; ++i) {
	//					if (logs[i]->getEventName() == eventName) {
	//						std::vector<double> totals = logs[i]->getVector();
	//						means[i] = findMean(totals);
	//						stdDivs[i] = sqrt(findVariance(totals, means[i]));
	//						break;
	//					}
	//				}
	//			}
	//		}
	//
	//		writeStats(means, stdDivs);










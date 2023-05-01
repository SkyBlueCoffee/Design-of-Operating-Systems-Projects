#ifndef ASSIGNMENT00_GRIFFITH_JONATHAN_SUMMARY_DATA_H
#define ASSIGNMENT00_GRIFFITH_JONATHAN_SUMMARY_DATA_H
//Include guards

struct summaryData{ //Defines a struct named "summaryData" to hold data for each user in the program
	long long id;             //Id of user
	char field[12][250];//Meta data fields to summarize
	double value[12];      //Values of the meta data to summarize
};

extern struct summaryData summaryArray[33]; //External definition for summaryData, telling the program it is defined elsewhere

#endif

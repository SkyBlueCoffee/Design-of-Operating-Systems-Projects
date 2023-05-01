#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment00_griffith_jonathan_summary.h"
#include "assignment00_griffith_jonathan_summaryData.h"

struct summaryData summaryArray[33]; //Definition for an array of structs of type summaryData, called summaryArray. Used in summary.c and action.c

void summary(){
	//Function to create a summary of the data obtained in readArray
	char metaData[12][100]; //2D char array to hold the meta data fields
	double averageCalories = 0;
	strcpy(metaData[0], "averageCalories"); //I hate that I had to do this
	double averageSedentaryMinutes = 0;
	strcpy(metaData[1], "averageSedentaryMinutes");
	double averageLightlyActiveMinutes = 0;
	strcpy(metaData[2], "averageLightlyActiveMinutes");
	double averageFairlyActiveMinutes = 0;
	strcpy(metaData[3], "averageFairlyActiveMinutes");
	double averageVeryActiveMinutes = 0;
	strcpy(metaData[4], "averageVeryActiveMinutes");
	double averageSedentaryActiveDistance = 0;
	strcpy(metaData[5], "averageSedentaryActiveDistance");
	double averageLightActiveDistance = 0;
	strcpy(metaData[6], "averageLightActiveDistance");
	double averageModeratelyActiveDistance = 0;
	strcpy(metaData[7], "averageModeratelyActiveDistance");
	double averageVeryActiveDistance = 0;
	strcpy(metaData[8], "averageVeryActiveDistance");
	double averageSteps = 0;
	strcpy(metaData[9], "averageSteps");
	double startWeightKg = 0;
	double weightLossKg = 0;
	strcpy(metaData[10], "weightLost_inKg");
	double startWeightLbs = 0;
	double weightLossLbs = 0;
	strcpy(metaData[11], "weightLost_inLbs");
	
	int users = 33; //Amount of users who's data has been collected. In this case, 33 users.
	char weightLossData[2000][250];
	FILE* fileData4; //FILE variable to open weightLoss.txt
	FILE* readFileData; //FILE variable to open readFileTemporary.txt
	
	int i = 0; //Yay temp variable i is back
	int j = 0; //i's brother, j, is here too
	int k = 1;
	double n = 0;
	
	fileData4 = fopen("weightLoss.txt", "r"); //Opens weightLoss.txt with a read option
	
	while(!feof(fileData4)){ //Continues the loops until the end of file for "weightLoss.txt"
		fgets(weightLossData[i], 250, fileData4); //Gets each line of fileData4 and places it into weightLossData
		
		i++; //Increments i
		
		if(feof(fileData4)){ //Checks once again if the end of file has been reached and breaks if so
		    break;
		}
	}
	fclose(fileData4); //Closes weightLoss.txt
	
	for(i = 0; i < users; i++){
	    char *tempPtr; //A temporary char point to use in the next line
	    char *garbage = malloc(sizeof(char) * 15); //char pointers to toss garbage data into idk
	    char *moreGarbage = malloc(sizeof(char) * 15);
	    
	    readFileData = fopen("readFileTemporary.txt", "r"); //Opens the readFile array saved to a txt file
	    fileData4 = fopen("weightLoss.txt", "r"); //Opens weightLoss.txt, but again
	
	    summaryArray[i].id = strtol(weightLossData[k], &tempPtr, 10); //Strtol takes the int at the begining of each line in weightLossData, the id, and assigns it to the id field in each struct in summarayArray
	    
	    while(!feof(readFileData)){
	        char temp[250];
	        fscanf(readFileData, "%s", temp); //Puts the current line of readFileTemporary.txt into a temp string
	        long long id = strtol(temp, &tempPtr, 10); //Grabs the current line's user ID
	        if(summaryArray[i].id == id){ //During the loop, compares the current user ID to the ID in summaryArray[i] and continues if they're the same
	            n++; //n keeps tracks of the number to average by later
	            garbage = strtok(temp, ","); //Skips ID column
	            garbage = strtok(NULL, ","); //Skips ActivityDay column
	            averageCalories += strtol(garbage, &tempPtr, 10); //Adds calories coulmn to averageCalories
	            garbage = strtok(NULL, ",");//Skips calories column
	            garbage = strtok(NULL, ","); //Skips ID column
	            garbage = strtok(NULL, ","); //Skips ActivityDay column
	            averageSedentaryMinutes += strtol(garbage, &tempPtr, 10);
	            garbage = strtok(NULL, ","); //Skips sedentaryminutes column
	            averageLightlyActiveMinutes += strtol(garbage, &tempPtr, 10); //Adds lightlyactiveminutes column to averageLightlyActiveMInutes
	            garbage = strtok(NULL, ","); //Skips lightlyactiveminutes column
	            averageFairlyActiveMinutes += strtol(garbage, &tempPtr, 10); //Adds fairlyactiveminutes column to averageFairlyActiveMinutes
	            garbage = strtok(NULL, ","); //Skips fairlyactiveminutes column
	            averageVeryActiveMinutes += strtol(garbage, &tempPtr, 10); //Adds veryactiveminutes column to averageVeryActiveMinutes
	            garbage = strtok(NULL, ","); //Skips veryactiveminutes column
	            averageSedentaryActiveDistance += strtol(garbage, &tempPtr, 10); //Adds sendentaryactivedistance to averageSedentaryActiveDistance
	            garbage = strtok(NULL, ","); //Skips sedentaryactivedistance column
	            averageLightActiveDistance += strtol(garbage, &tempPtr, 10); //Adds lightactivedistance column to averageLightActiveDistance
	            garbage = strtok(NULL, ","); //Skips lightactiveminutes column
	            averageModeratelyActiveDistance += strtol(garbage, &tempPtr, 10); //Adds moderatelyactivedistance column to averageModeratelyActiveDistance
	            garbage = strtok(NULL, ","); //Skips moderatelyactivedistance column
	            averageVeryActiveDistance += strtol(garbage, &tempPtr, 10); //Adds veryactivedistance column to averageVeryActiveDistance
	            garbage = strtok(NULL, ","); //Skips veryactivedistance column
	            garbage = strtok(NULL, ","); //Skips ID column
	            garbage = strtok(NULL, ","); //Skips ActivityDay column
	            averageSteps += strtol(garbage, &tempPtr, 10); //Adds steps to averageSteps
	        }
	        
	        if(feof(readFileData)){ //Checks again if the end of the file has been reached
	            break;
	        }
	    }
	    while(!feof(fileData4)){
	        char otherTemp[250];
	        fscanf(fileData4, "%s", otherTemp); //Puts the current line of weightLoss.txt into the other temp string
	        int id = strtol(otherTemp, &tempPtr, 10); //Grabs the current line's user ID
	        if(summaryArray[i].id == id){ //During the loop, compares the current user ID to the ID in summaryArray[i] and continues if they're the same
				moreGarbage = strtok(otherTemp, ","); //Sets inital token
				moreGarbage = strtok(NULL, ","); //Skips ID column
				startWeightKg = strtol(moreGarbage, &tempPtr, 10); //Puts the startWeight, Kg column into startWeightKg
				moreGarbage = strtok(NULL, ","); //Skips startWeight, Kg column
				startWeightLbs = strtol(moreGarbage, &tempPtr, 10); //Puts the startWeight, Lbs column into startWeightLbs
				moreGarbage = strtok(NULL, ","); //Skips startWeight, Lbs column
				moreGarbage = strtok(NULL, ","); //Skips startbmi column
				weightLossKg = strtol(moreGarbage, &tempPtr, 10); //Puts the endWeight, Kg column into weightLossKg
				moreGarbage = strtok(NULL, ","); //Skips endWeight, Kg column
				weightLossLbs = strtol(moreGarbage, &tempPtr, 10); //Puts the endWeight, Lbs column into weightLossLbs
				
				if(feof(fileData4)){ //Checks again if the end of the file has been reached
	                break;
	            }
	        }
	    }
	    	    
	    averageCalories /= n; //Averages out our data using n, which was tracked during the loop
	    averageSedentaryMinutes /= n;
	    averageLightlyActiveMinutes /= n;
	    averageFairlyActiveMinutes /= n;
	    averageVeryActiveMinutes /= n;
	    averageSedentaryActiveDistance /= n;
	    averageLightActiveDistance /= n;
	    averageModeratelyActiveDistance /= n;
	    averageVeryActiveDistance /= n;
	    averageSteps /= n;
	    weightLossKg = startWeightKg - weightLossKg; //Subtracts the end weights from the start weights to find weight loss
	    weightLossLbs = startWeightLbs - weightLossLbs;
	    
	    for(j = 0; j < 12; j++){
	    	strcpy(summaryArray[i].field[j], metaData[j]); //Assigns the metadata to the field string array for each struct in summarayArray	    	
		}
		summaryArray[i].value[0] = averageCalories; //Assigns the average values calulated earlier into the value array for summaryArray
		summaryArray[i].value[1] = averageSedentaryMinutes;
		summaryArray[i].value[2] = averageLightlyActiveMinutes;
		summaryArray[i].value[3] = averageFairlyActiveMinutes;
		summaryArray[i].value[4] = averageVeryActiveMinutes;
		summaryArray[i].value[5] = averageSedentaryActiveDistance;
		summaryArray[i].value[6] = averageLightActiveDistance;
		summaryArray[i].value[7] = averageModeratelyActiveDistance;
		summaryArray[i].value[8] = averageVeryActiveDistance;
		summaryArray[i].value[9] = averageSteps;
		summaryArray[i].value[10] = weightLossKg;
		summaryArray[i].value[11] = weightLossLbs;
		
		k++;
		
		averageCalories = 0; //Resets all values to zero
	    averageSedentaryMinutes = 0;
	    averageLightlyActiveMinutes = 0;
	    averageFairlyActiveMinutes = 0;
	    averageVeryActiveMinutes = 0;
	    averageSedentaryActiveDistance = 0;
	    averageLightActiveDistance = 0;
	    averageModeratelyActiveDistance = 0;
	    averageVeryActiveDistance = 0;
	    averageSteps = 0;
	    weightLossKg = 0;
	    weightLossLbs = 0;
	    n = 0;
	    
	    
	    fclose(fileData4); //Closes weightLoss.txt
        fclose(readFileData); //Closes readFileTemporary.txt
    }
}


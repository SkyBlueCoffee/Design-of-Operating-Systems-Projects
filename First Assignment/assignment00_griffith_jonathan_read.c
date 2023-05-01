#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment00_griffith_jonathan_read.h"

void readFile(){
	//Function used to grab data from the input files "dailyCalories.txt", "dailyIntensities.txt", and
	//"dailySteps.txt" and compiles it all into a dynamic array "readArray".
	FILE* fileData1; //FILE type variables used to open the data files for reading
	FILE* fileData2;
	FILE* fileData3;
	char** readArray; //Declaration of the dynamic 2D array "readArray" to be used in the rest of the program
	char caloriesArray[2000][250];		//Three temporary arrays to hold all items in the files
	char intensitiesArray[2000][250];	//Size 2000 char arrays that accepts strings of length 200
	char stepsArray[2000][250];		//These arrays will then be compiled into a single dynamic array
	int i = 0; //i, the temp variable for loops. It's always the letter i for some reason
	int arrayLen = 0; //Keeps track of the size of the array

	fileData1 = fopen("dailyCalories.txt", "r"); //Each file is opened with the "r" option to read
	fileData2 = fopen("dailyIntensities.txt", "r");
	fileData3 = fopen("dailySteps.txt", "r");
	
	while(!feof(fileData1)){ //Loop that continues until the program reaches the end of the file
    	fscanf(fileData1, "%s", caloriesArray[i]); //Scans each line of each file and places it into the three temporary arrays
    	fscanf(fileData2, "%s", intensitiesArray[i]);
    	fgets(stepsArray[i], 250, fileData3); //This one is done differently because we want a trailing newline in our array
    	
		arrayLen++; //Keeps track of the size of the array
    	
		if(feof(fileData1)){ //Checks again if the program has reached the end of the file.
	        break;
	    }
	    i++; //Increments i
    }
	
	fclose(fileData1); //Closes each of the files opened for reading now that we're done
	fclose(fileData2);
	fclose(fileData3);

    readArray = malloc(arrayLen * sizeof(char*)); //Allocates memory for readArray using the size of char* and the array length counted earlier
	for(i = 0; i < arrayLen; i++){
		readArray[i] = malloc(arrayLen * sizeof(char)); //Allocates memory for each entry in readArray
		sprintf(readArray[i], "%s,%s,%s", caloriesArray[i], intensitiesArray[i],stepsArray[i]); //Combines the arrays into readArray
	}
	
	FILE *writeData = fopen("readFileTemporary.txt", "wb"); //Opens new file readFileTemporary to write to
	for(i = 0; i < arrayLen; i++){
	    fprintf(writeData, "%s", readArray[i]); //Writes each line of readArray to readFileTemporary.txt
	}
	fclose(writeData); //Closes readFileTemporary.txt
	
	free(readArray); //Frees up the memory allocated for readArray now that we're done with it
}

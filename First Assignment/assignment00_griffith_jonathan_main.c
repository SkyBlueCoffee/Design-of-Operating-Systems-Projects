/*
*Author Name: Jonathan Griffith
*Email: jonathan.griffith@okstate.edu
*Date: 9/10/2022
*Program Description: Takes four files (dailyCalories.txt, dailyIntensities.txt, dailySteps.txt, and weightLoss.txt), reads the data
*in the files and averages the data in them, then either saves the summerized data averages to a new file or prints one user's
*data file to the screen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment00_griffith_jonathan_read.h"
#include "assignment00_griffith_jonathan_summary.h"
#include "assignment00_griffith_jonathan_action.h"

int main(int argc, char *argv[]){
	//Main driver function, used to call the other functions of the program.
	char actionCommand[6]; //Variable to store the action command
	char outputFile[50] = "summary.txt"; //Variable to store the desired name of the output file
	strcpy(actionCommand, argv[1]); //The first argument is the action save/print
	if(argc == 3){ //Checks if the user has inputed two command line arguments
	   strcpy(outputFile, argv[2]); //If so, copies the second command into outputFile variable
    }
    else{
        strcpy(outputFile, "summary.txt"); //Base case if the user only entered one argument
    }
	
	readFile(); //Calls readFile()
    summary(); //Calls summary()
    action(actionCommand, outputFile); //Calls action() with the actionCommand grabbed from the command line argument
}

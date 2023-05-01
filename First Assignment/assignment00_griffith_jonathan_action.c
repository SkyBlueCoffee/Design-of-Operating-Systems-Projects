#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment00_griffith_jonathan_action.h"
#include "assignment00_griffith_jonathan_summaryData.h"

void action(char* actionCommand, char* outputFile){
    char* save = "save"; //Char* variables for save and print for comparisons with commandAction
    char* print = "print";
    long long id; //Id variable used to let the user choose a user to print to screen
    
    if(strcmp(actionCommand, save) == 0){ //If the command passed was save, saves the summary data to a file
        FILE* saveData = fopen(outputFile, "wb"); //Opens summary.txt with the option to write
        for(int i = 0; i < 33; i++){ //Loops through all 33 users in summaryArray
            fprintf(saveData, "%lld\n", summaryArray[i].id); //Prints the id to file
            for(int j = 0; j < 12; j++){ //Loops through the 12 fields that is summerized
                fprintf(saveData, "%s = %f\n", summaryArray[i].field[j], summaryArray[i].value[j]); //Prints the metaData field and the value of that field to file
            }
            fprintf(saveData, "\n"); //Extra newline to look more organized in the file.
        }            
    }
    else if(strcmp(actionCommand, print) == 0){ //If the command passed was print, prints a user's summary to the screen
    	printf("Please enter the respondent ID: ");
    	scanf("%lld", &id);
    	for(int i = 0; i < 33; i++){
    		if(summaryArray[i].id == id){
		    	printf("For the repondent with ID %lld, the summary is\n", summaryArray[i].id);
    			for(i = 0; i < 12; i++){
    				printf("%s = ", summaryArray[i].field[i]);
    				printf("%f\n", summaryArray[i].value[i]);
    			}
    			break;
    		}
    	}
    }
    else{ //If the command passed isn't reconized, warns the user and does nothing.
        printf("Action not recognized, please check your input.\n");
    }
}

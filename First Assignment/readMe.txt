Description:
A survey has been conducted via Amazon Mechanical Turk between 03/12/2016 – 05/12/2016 to collect personal tracker data. You are provided with the dataset that are submitted by some of the eligible Fitbit users. These datasets are provided in the format of 4 .txt files. Your task is to write a C program to summarize these datasets, following the specific requirements as mentioned later in this assignment.
The main function acts as a driver function which just calls all other functions. All other functions are called only from this function.
The readFile function reads the input file(s), except weightLoss.txt. This function needs to use a dynamic 2D array, let us call it a readArray, using the initial size as given in the command-line argument(s).
The summary function makes use of the weightLoss.txt file along with the 2D dynamic array created in the readFile function to make the summary of the dataset.
If the 2nd argument in the command-line argument is “save”, then the action function saves the summaryStructureArray in the output file specified in the command-line argument (i.e. summary.txt), well-formatted just like readFileTemporary.txt. However, if the 2nd argument in the command-line argument is “print”, then this action function will display the summary data of a specific respondent on the screen. For this, this function needs to ask user to enter the respondent ID. For that respondent ID, the action function displays all the averaged value from the summaryStructureArray.

Examples:
1. ./a.out save dailyCalories.txt 3 summary.txt
In this case the readFile function needs to read only one inputfile i.e. dailyCalories.txt. To store the contents of this file, this function creates a readArray with an initial column size of 3 (given in the command line argument).
2. ./a.out save dailyCalories.txt 3 dailyIntensities.txt 10 dailySteps.txt 3 weightLoss.txt 7 summary.txt
In this case the readFile function needs to read the input files (dailyCalories.txt, dailyIntensities.txt and dailySteps.txt) in the order as they appear.
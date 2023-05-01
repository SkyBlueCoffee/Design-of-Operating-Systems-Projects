/*
* Function Description: Opens the file determined from the function call and searches for the book also determined from
* the function call. If the book is found, it closes the file and prints the book data. If not, it prints that the bookName 
* couldn't be found. The function also prints when a file is opened and closed to terminal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "assignment01_griffith_jonathan_shared.h"

extern pthread_mutex_t mutex; //Mutex to prevent race conditions in threads

void *readFiles(void *args){ //Argument is a pointer to the struct created in main
    struct arguments *bookStuff = args;

    char *bookName = malloc(sizeof(char) * 100);
    char *fileName = malloc(sizeof(char) * 100);
    bookName = bookStuff->book; //Sets the book name to search for from the argument struct's book variable
    fileName = bookStuff->file; //Sets the file to search in from the argument struct's file variable
    pthread_mutex_unlock(&mutex); //Unlocks the mutex
    	    
    int i = 0;
    FILE* fileData; //Variable to read input files
    char *outFile = malloc(sizeof(char) * 50);
    char temp[2500000]; //Temp variable to hold data from files
    int bookFound;
    
    char bookInfo[5000000]; //Variable to hold book data in
    char *title = malloc(sizeof(char) * 100);
    
    strcpy(outFile, bookName); //Used to open a temp file to hold book info
    strcat(outFile, ".txt");
    fileData = fopen(fileName, "r"); //Opens the defined file with the read option
    FILE* outdata;
    printf("%s opened\n", fileName);
    
    while(!feof(fileData)){ //Scans the file until reaching the end
        fgets(temp, sizeof(temp), fileData); //Scans the current line in the file
        strcpy(bookInfo, temp); //Copies current line to bookInfo varialbe
        strcpy(title, strtok(temp, ",")); //Grabs the title column
        
        if(strcmp(title, bookName) == 0){ //Compares the current title with the requested book
            printf("Found \'%s\' in %s\n", title, fileName); //Prints that the book was found in the current file
            bookFound = 1; //Sets a flag that the book was found
            outdata = fopen(outFile, "w"); //Opens a new file with write option using the outFile varialbe
            fprintf(outdata, "Title: %s\n", strtok(bookInfo, ",")); //Writes the book's data to the temp file
            fprintf(outdata, "Genre: %s\n", strtok(NULL, ","));
            fprintf(outdata, "Rating: %s\n", strtok(NULL, ","));
            fprintf(outdata, "Summary: %s\n", strtok(NULL, "\""));
            fclose(outdata);
            printf("Printed \'%s\' data to %s\n", title, outFile);
            break;
        }
        if(feof(fileData)){ //Checks again if the end of the file has been reached
	        break;
	    }
    }
    if(bookFound == 0){ //If the book found flag wasn't lifted, pritns that the specified book wasn't found
        printf("Book \'%s\' not found!\n", bookName);
    }
    fclose(fileData); //Closes the file
    printf("File \'%s\' closed siccessfully\n", fileName); //Prints that the file was closed.
}

/*
*Author Name: Jonathan Griffith
*Email: jonathan.griffith@okstate.edu
*Date: 10/24/2022
*Program Description: Prompts the user to enter N number of books, with the user determining N. The program then searches the
*files provided in the command line arugments for each of those books, using new threads to do so.
*After all threads have finished searching for books and printing their data to seperate .txt files, all threads are joined
*and the user is informed the search is complete.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "assignment01_griffith_jonathan_read.h"
#include "assignment01_griffith_jonathan_shared.h"

pthread_mutex_t mutex;

int main(int argc, char *argv[]){    
    if(argc <= 1){ //No agruments given in command line
        printf("No file given!\n");
        exit(1);
    }
    int numFiles = argc - 1; //Grabs the number of arguments given in the command line
    int numBooks;
    char **userInput;
    
    struct arguments bookStuff; //Creates a new arguments struct called bookStuff to pass arguments to readFiles
    bookStuff.file = malloc(sizeof(char) * 1000);
    bookStuff.book = malloc(sizeof(char) * 1000);
    
    char temp[50]; //Temp string to grab data before passing to another variable
    
    int i;
    int j;

    pthread_t tid[numFiles]; //Thread ID used to create threads
    pthread_mutex_init(&mutex, NULL);
    
    printf("%d files to load\n", numFiles); //Prints the number of files the user put into the command line
    printf("Enter the number of books to search for: "); //Prompts the user for how many books to search for
    scanf("%d", &numBooks);
   
    userInput = malloc((sizeof(char) * 50) * numBooks); //userInput is allocated using the number of books to search for
    j = numBooks;
    fgets(temp, sizeof(temp), stdin); //Idk why this needs to be here but it scans a single newline from somewhere
    for(i = 0; i < numBooks; i++){ //Loops for numBooks amount of times, prompting the user for a book title each time
        printf("Enter a book to search for (%d more): ", j);
        fgets(temp, sizeof(temp), stdin); //Book name scanned from user input into a temp variable
        temp[strcspn(temp, "\n")] = '\0'; //Replaces the trailing newline from temp with a NULL character
        userInput[i] = strdup(temp); //Temp variable is passed into the userInput array
        j--;
    }
    
    printf("Books to search for: "); //Prints what books to search for
    for(i = 0; i < numBooks; i++){
        printf("\'%s\' ", userInput[i]);
        
    }
    printf("\n\n");
    
    for(i = 0; i < numFiles; i++){ //Loops for the numbers of books to search for
    	for(j = 0; j < numBooks; j++){ //Loops for the number of files to search
    	    pthread_mutex_lock(&mutex); //Sets the mutex lock to let the thread pass shared struct data into local variables
    	    bookStuff.file = argv[i+1]; //Sets the file name in struct to current iteration
    	    bookStuff.book = userInput[j]; //Sets the book name in struct to current iteration
    	    pthread_create(&tid[i], NULL, readFiles, (void *)&bookStuff); //Creates a new thread to run readFiles with the struct as an argument
    	}
    }
    sleep(1); //Sleeps for a second to prevent threads from being joined before completing their task.
    
    for(i = 0; i < numFiles; i++){
        pthread_join(tid[i], NULL); //Joins all threads
    }
    
    printf("\nSearch Completed\n"); //Prints that the search was completed
}

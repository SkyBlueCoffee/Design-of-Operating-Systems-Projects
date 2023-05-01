/*
*Group Names: Mujahid Egan, Charlie Miller, Vamsi Lakshman Varma Datla, Anthony Horinek, Jonathan Griffith, Douglas Edmondson
*Author: Jonathan Griffith
*Date: 12/05/2022
*Program Description: Simulate a jewlery store
*/

#include <stdio.h> //The usual stuff
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/socket.h> //Server stuff
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

#include "message_queue.h"
#include "storeInventory.h"
#include "customerQueue.h"
#include "assistantInfo.h"
#include "simpleSocket.h"
#include "assistantoptions.h"

#include "clientHandler.c"
#include "charlie_assistant.c"

#define MAXCHAR 1024
#define PORT 1414
#define IP "127.0.0.1"

//cleanup shared memory from previous execution
void initialize_sharedMemory_destroy() {
    sharedMem_destroyAssistants();
    sharedMem_destroyStoreInventory();
    sharedMem_destroyCustomerQueue();
    sharedMem_destroyMessageQueue(); //destroy message queue
}

//shared memory manipulators
assistants* initialize_allAssistants() {
    //mount assistant info into memory
    sharedMem_destroyAssistants(); //destroy shared memory
    assistants* assts = sharedMem_getAssistantInfo();
    if (assts == NULL) printf("failed to mount shared memory for assistants\n");
    return assts;
}
storeInventory* initialize_storeInventory() {
    //store inventory 
    sharedMem_destroyStoreInventory();//clear out existing memory
    storeInventory* stinv = sharedMem_getStoreInventory(); //mount shared memory to this scope
    if (storeInventory_parseCatalog(stinv,CATALOG_FILEPATH) == 0) {printf("failed to parse store catalog. aborting.\n"); exit(0);} 
    return stinv;
}
customerQueue* initialize_customerQueue(int nsofas,int nspaces) {
    customerQueue* cq = sharedMem_setupCustomerQueue(nsofas, nspaces ); 
    if (dbg && (cq != NULL)) printf("server @pid[%d] set up a customer queue (p:%p) with %d sofas and %d total waiting spaces\n",getpid(),cq,cq->numSofas,cq->maxWaiting);
    return cq;
}


messageQueue* initialize_messageQueue() {
    messageQueue* m = sharedMem_getMessageQueue();
    m->boxes[9].messages[4].sender_pid = 144;
    return sharedMem_getMessageQueue();
}

/*void spawnAssistants(int nassistants) {
    assistants* allasst = sharedMem_getAssistantInfo();//mount shared memory to this scope
    for (int i = 0 ; i < nassistants; i++) { 
        int thispid = fork();
        if (thispid == 0) {//child 

        //add this process (a new assistant process) to the assistants structure
            assistantInfo* myself = assistantInfo_new(allasst);//make an entry in assistant info for me
            
            if (dbg) printf("assistant #%d spawned @pid:[%d]\n",myself->assistantNumber,getpid());
        
        //call assistant subroutine - subroutine SHOULD clean up this process, but handle errors if it does not. 
            if (assistantSubroutine() == 1) 
                printf("assistant process [%d] finished with SUCCESS, but subroutine failed to destroy itself. exiting\n",getpid());
            else 
                printf("assistant process [%d] finished - FAIL. Exiting.\n",getpid());
            exit(0);


        }
        else continue; //parent continues executing loop for each assistant process
    }
            

}*/

int main(int argc, char *argv[]){    
    if(argc != 4){ //No agruments given in command line
        printf("Invalid number of arugments\n");
        exit(1);
    }
    int numAssistants;
    int numSofas;
    int maxCustomers;
    
    sscanf(argv[1], "%d", &numAssistants); //Converts the command line arguments to ints and places them into variables
    sscanf(argv[2], "%d", &numSofas);
    sscanf(argv[3], "%d", &maxCustomers);
    
    initialize_sharedMemory_destroy(); //Clears shared memory
    assistants* allAssistants     = initialize_allAssistants(); //Prepares memory for assistants
    storeInventory* stinv   = initialize_storeInventory(); //Initializes the store inventory
    customerQueue* cq       = initialize_customerQueue(numSofas, maxCustomers); //Initializes the customer queue
    messageQueue* msgq      = initialize_messageQueue(); //Initializes the message queue
    printf("Message queue prepared.\n");
    
	for (int i = 0; i < numAssistants; i++) {
		int f = fork();
		if (f == 0){ //child process is an assistant
		    printf("assistantHandler called.\n");
			assistantSubroutine(stinv); //call the assistant subroutine
			exit(1);
		}
		else {
			allAssistants = sharedMem_getAssistantInfo(); //update the assistant info shared memory
		}
	}
	
    int server_socket, client_socket; //Server variables
    struct sockaddr_in server_addr = {0}, client_addr = {0};
    socklen_t addr_size;
    char buffer[MAXCHAR];
    pid_t clientPID;
    int binding;
    
    int currentCustomers = 0;
    
    server_socket = socket(AF_INET, SOCK_STREAM, 0); //Creates a server socket to accept clients
    if(server_socket < 0){
        perror("Socket error!\n"); //Exits if the socket cannot be made
        exit(1);
    }
    printf("TCP server socket created.\n");
    
    memset(&server_addr, '\0', sizeof(server_addr)); //Sets the server information using the predefined PORT and IP variables
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    // server_addr.sin_addr.s_addr = inet_addr(IP);
    
    binding = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)); //Attempts to bind the socket to the port and IP
    if(binding < 0){
        perror("Bind error\n"); //Exits if the socket cannot be bound to the IP
        exit(1);
    }
    printf("Bound to port number: %d\n", PORT);
    
    if(listen(server_socket, maxCustomers) == 0){ //Listens for clients to connect, with the max queue set to maxCustomers
        printf("Listening...\n");
    }
    else{
        printf("Bind error\n");
    }
    
    for(;;){ //Indefinate for loop to hold all client and server interaction within
    	addr_size = sizeof(client_addr); //Sees that a client is trying to connect and accepts their socket info
    	client_socket = accept(server_socket, (struct sockaddr_in*)&client_addr, &addr_size);
    	if(client_socket < 0){
    		printf("Client connection error\n");  //Exits if the client can not be accepted
    		exit(1);
		}
		currentCustomers += 1;
		if((clientPID = fork()) == 0){ //Creates a fork, for which the child takes control of handling the connected client
            //close(server_socket);
            
            printf("Client connected from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            customerInfo cust = {client_socket, cq->totalCustomers, -1, getpid(), 0};
            for(;;){
                bzero(buffer, sizeof(buffer)); //Empties buffer to prepare to send message
                snprintf(buffer, sizeof(buffer),"Hello Client #%d\n", currentCustomers); //Loads message into buffer
                send(client_socket, buffer, strlen(buffer), 0); //Sends the buffer through the client's socket
                
                if (clientHandler(&cust) == 1){//evoke client handler subroutine
                    printf("clientHandler called.\n");
                    break;
                }
                else{
                    printf("clientHandler failed to be called\n");
                }
            }
        }
	}
	
	close(client_socket); //Closes connection with the client and prints to terminal they have disconnected
	printf("Client %s:%d has disconnected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
}

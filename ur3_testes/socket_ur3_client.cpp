// Server side C/C++ program to demonstrate Socket programming 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <string> 
#include <stdlib.h>
#include <sstream>
#define PORT 5000

int main(){ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char *hello = "Hello from server"; 

	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 

	// Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}

	if (listen(server_fd, 3) < 0){ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	}
    ///////////////////////
	
    int8_t buffer_in[128];
	int8_t buffer_out[128]; 

   	/////////////////////////////
	FILE *fp;
    char filename[20]= "pitu.csv";
	fp=fopen(filename,"w+");
	fprintf(fp,"tempo, vel\n");
    float tempo = 0;
	float vel = 0; 
	///////////////////////
    while (1){
	send(new_socket, &buffer_in, sizeof buffer_in, 0);
    valread = recv(new_socket, &buffer_out, sizeof buffer_out, 0);
	memcpy(&vel,&buffer_out[0], sizeof(float));
	fprintf(fp,"\n%f %f",tempo, vel);
	tempo = tempo + 0.008; 
	}
	
	fclose(fp);
	return 0;
} 

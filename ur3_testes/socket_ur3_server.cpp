// Server side C/C++ program to demonstrate Socket programming 
#include <pthread.h>
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
#include <inttypes.h>
#define PORT 5000
int converter(int32_t num){
	uint32_t b0,b1,b2,b3;
	uint32_t res;

	b0 = (num & 0x000000ff) << 24u;
	b1 = (num & 0x0000ff00) << 8u;
	b2 = (num & 0x00ff0000) >> 8u;
	b3 = (num & 0xff000000) >> 24u;

	res = b0 | b1 | b2 | b3;

	return res;
}

int main(){ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	//char *hello = "Hello from server"; 
	// criação da thread

	
	//pthread_join(t1, NULL);

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
	
    int32_t buffer_in  = 0;
	int8_t buffer_out[4]; 

   	/////////////////////////////
	FILE *fp;
    char filename[20]= "pitu.csv";
	fp=fopen(filename,"w+");
	fprintf(fp,"tempo, vel\n");
    float tempo = 0;
	double vel_float = 0;
	int64_t vel_int64 = 0;
	int32_t vel_int32 = 0;
	float norma_float = 1000000.0;
	float vel_var = 0;
	float sinal = 1;
	 
	///////////////////////
	// chamando a thread
	//////////////////////////fffffff6
    while (1){
		buffer_in = (int)(vel_var*norma_float);
		buffer_in = converter(buffer_in);
		send(new_socket, &buffer_in, sizeof buffer_in, 0);
    	valread = recv(new_socket, &buffer_out, sizeof buffer_out, 0);
		memcpy(&vel_int64, &buffer_out[0], sizeof(int64_t));
		vel_int32 = converter(vel_int64);
		vel_float = ((double)vel_int32)/norma_float;
		fprintf(fp, "\n%f, %f", tempo, vel_float);
		printf("%f\n", vel_float);
		tempo = tempo + 0.008; 
		vel_var  = vel_var + 0.01*sinal;
		if(vel_var >= 2){
			sinal  = sinal*(-1);
		}

		if(vel_var <= -2){
			sinal  = sinal*(-1);
		}

	}
	

	fclose(fp);
	return 0;
} 

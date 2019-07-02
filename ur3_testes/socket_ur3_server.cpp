// Programa para teste na junta 5 do ur3////////////////////////////////
// compilar : g++ -std=c++11 socket_ur3_server.cpp -o server -lpthread//
////////////////////////////////////////////////////////////////////////
#include <X11/keysymdef.h>
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
#include "open_socket.h"
#define PORT 5000
#include <thread> 
using namespace std;

char c = 'w';
float velthead = 0;

/// little endian <-> big endian ///////
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
///////////////////////////////////////

int main(){ 	
    ///////////////////////
	//thread t1(muda_vel); 
	//t1.join();
	int new_socket;
	// abrindo a comunicaçção tcp socket
	new_socket = open_socket();
	////////////////////////////////////
	// Declaração dos buffers de entrada e saida 
    int32_t buffer_in  = 0;
	int8_t buffer_out[4]; 
   	/////////////////////////////
	// criação de um arquivo .csv para armazenar os dados
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
	//////////////////////////fffffff6
    while (1){
		buffer_in = (int)(velthead*norma_float);
		buffer_in = converter(buffer_in);
		send(new_socket, &buffer_in, sizeof buffer_in, 0);
    	recv(new_socket, &buffer_out, sizeof buffer_out, 0);
		memcpy(&vel_int64, &buffer_out[0], sizeof(int64_t));
		vel_int32 = converter(vel_int64);
		vel_float = ((double)vel_int32)/norma_float;
		fprintf(fp, "\n%f, %f", tempo, vel_float);
		printf("ref = %f  saida = %f \n", velthead, vel_float);
		tempo = tempo + 0.008;
		//printf("\n%i",soma(1,2)); 
	
	}
	fclose(fp);
	return 0;
} 

// Programa para teste na junta 5 do ur3////////////////////////////////
// compilar : g++ open_socket.cpp socket_ur3_server.cpp -o server///////
////////////////////////////////////////////////////////////////////////
#include <X11/keysymdef.h>
#include <sys/socket.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <iostream>
#include <stdio.h>   
#include <string.h> 
#include <unistd.h>  
#include <fcntl.h>   
#include <errno.h>   
#include <termios.h> 
#include <string> 
#include <stdlib.h>
#include <sstream>
#include <inttypes.h>
#include <math.h>
#include "open_socket.h"
#include "send_script.h"

#define PORT 5000
#define PI 3.1415
using namespace std;

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
	// primeira coisa:
	// tem que enviar o arquivo urscript
	send_script(); // a função send_script envia o arquivo para o robô
	///////////////////////////////////
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
	int conta = 0;
	///////////////////////

	///////////////////////
    while (1){
		velthead = sin ((conta*PI)/180);
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
		conta = conta + 1;
			
	}
	fclose(fp);
	return 0;
} 

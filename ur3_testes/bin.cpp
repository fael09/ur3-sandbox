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
#include <stdio.h>
#include <pthread.h>
float velthead  = 0;
void * muda_vel(void *arg){
	char c = 'a';
	if(c == 'a'){
		velthead = velthead + 0.01;
	}
	if(c == 'd'){
		velthead = velthead - 0.01;
	}
}

int main(){

    pthread_t t1;
	int a1 = 1;
	pthread_create(&t1, NULL, muda_vel,(void *)(&a1));
    pthread_join(t1, NULL);
while (1)
{
    printf("%f\n", velthead);

}

return 0;
}
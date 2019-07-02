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


int main(){
char c ;
while (1)
{
	c = getchar();
	getchar(); 
	getchar(); 

	//getchar();
	printf("%c",c);
}




return 0;
}
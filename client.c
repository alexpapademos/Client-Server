#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char *argv[])
{ 
	struct sockaddr_in sad; /* structure to hold an IP address */ 
	int clientSocket; /* socket descriptor */ 
	struct hostent *ptrh; /* pointer to a host table entry */ 
	char Sentence[128]; 
	char modifiedSentence[128]; 

	char* host = argv[1]; 
	int n, port = atoi(argv[2]);

	clientSocket = socket(PF_INET, SOCK_STREAM, 0); 
	memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure */ 
	sad.sin_family = AF_INET; /* set family to Internet */ 
	sad.sin_port = htons((u_short)port); 
	ptrh = gethostbyname(host); /* Convert host name to IP address */
	memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length); connect(clientSocket, (struct sockaddr *)&sad, sizeof(sad));
	
	//printf("Enter site: ")
	strcpy(Sentence, "GET www-net.cs.umass.edu/personnel/kurose.html");

	n=write(clientSocket, Sentence, strlen(Sentence)+1);  
	

	do{
		n=read(clientSocket, modifiedSentence, sizeof(modifiedSentence)); 
		printf("%s",modifiedSentence); 
	}while (n > 0);

	close(clientSocket); 
     
     return 0;                 
} 
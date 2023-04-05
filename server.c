#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[])
{ 
	struct sockaddr_in sad; /* structure to hold an IP address */ 
	struct sockaddr_in cad;
	int clientSocket; // socket to real server
	int welcomeSocket, connectionSocket; /* socket descriptor */ 
	struct hostent *ptrh; /* pointer to a host table entry */ 
	socklen_t alen;
	char clientSentence[1024 * 10];
	char modifiedSentence[128]; 
	char capitalizedSentence[128];
	int i, n, port = atoi(argv[1]), realServerPort = 80;
	char *realHost, *copy, *page, *token;
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);   
	memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure */ 
	sad.sin_family = AF_INET; /* set family to Internet */ 
	sad.sin_addr.s_addr = INADDR_ANY; /* set the local IP address */ 
	sad.sin_port = htons((u_short)port);/* set the port number */ 
	bind(welcomeSocket, (struct sockaddr *)&sad, sizeof(sad));

	/* Specify the maximum number of clients that can be queued */
	listen(welcomeSocket, 10);

	while(1) { 
	
	    connectionSocket=accept(welcomeSocket, (struct sockaddr *)&cad, &alen);
 
	    n=read(connectionSocket, clientSentence, sizeof(clientSentence)); 
 
	    /* capitalize Sentence and store the result in capitalizedSentence*/
		strcpy(capitalizedSentence, clientSentence);
		
		
		// dimiourgia aitimatos gia ton pragmatiko server
		copy = strdup(clientSentence);
		token = strtok(copy, " ");
		
		token = strtok(NULL, "/");		
		realHost = strdup(token);
		
		token = strtok(NULL, " ");
		if (token != NULL) page = strdup(token);
		else page = NULL;
		
	
		clientSocket = socket(PF_INET, SOCK_STREAM, 0); 
		memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure */ 
		sad.sin_family = AF_INET; /* set family to Internet */ 
		sad.sin_port = htons((u_short)realServerPort); 
		ptrh = gethostbyname(realHost); /* Convert host name to IP address */
		memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length); 
		
		strcpy(clientSentence, "GET /");//personnel/kurose.html");
		strcat(clientSentence, page);
		strcat(clientSentence, " HTTP/1.1\r\n");
		strcat(clientSentence, "HOST: ");//www-net.cs.umass.edu");
		strcat(clientSentence, realHost);
		strcat(clientSentence, "\r\n\r\n");

		
		connect(clientSocket, (struct sockaddr *)&sad, sizeof(sad));
		n=write(clientSocket, clientSentence, strlen(clientSentence)+1);  
		

		do{
			n=read(clientSocket, modifiedSentence, sizeof(modifiedSentence)); 

			if (n > 0){
				n = write(connectionSocket, modifiedSentence, strlen(modifiedSentence)+1);
			}
		}while (n != 0);
		
		close(clientSocket);
	    close(connectionSocket);  
    } 
} 

#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char argv[])
{
	struct sockaddr_in serv_addr;
	int sock_d;
	struct hostent *server;
	char msgp[45]="GET / HTTP/1.1\r\nHOST: api.ipify.org\r\n\r\n";
	char rcvmsgp[256],buff[16];
	
	sock_d = socket(AF_INET, SOCK_STREAM, 0);
	socklen_t slen = sizeof(serv_addr);
	bzero(&serv_addr,sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(80);
	server = gethostbyname("api.ipify.org");
	
	memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

	connect(sock_d, (struct sockaddr *)&serv_addr,sizeof(serv_addr));
	
	send(sock_d, msgp, strlen(msgp), 0);
	recv(sock_d, rcvmsgp, 200, 0);
	printf("What I got : %s\n",rcvmsgp);
	FILE *fp = fopen("ip.txt", "ab");
	if(fp!=NULL)
	{
		fputs(rcvmsgp,fp);
		fscanf(fp, "%[^\n]\n", buff);
	}
	printf("Your Public IP is :: %s\n", buff);
	fclose(fp);
	//char geo_lo_lat[60] = ""
}
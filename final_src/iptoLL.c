//the program is sending a HTTP request and result your public IP's LONG and LAT
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h>
#include "progrun.h"


//int 
//main(int argc, char argv[])
struct lon_lat iptoll()
{
	struct sockaddr_in serv_addr;
	int sock_d;
	struct hostent *server;
	
	//to send new line in C - \r\n
	
	char msgp[56]="GET / HTTP/1.1\r\nHOST: ipinfo.io\r\n\r\n";
	
	char lat[8], lon[8], rcvmsgp[512], parse_wd[16] = "\"loc\": \"";
	int web_len, pars_len, web_cnt = 0, pars_cnt = 0, pos, e, i, j = 0;
		
	if ((sock_d = socket (AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror ("SOCKET: error");
		exit (EXIT_FAILURE);
	}
	
//	socklen_t slen = sizeof (serv_addr);
	
	bzero (&serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons( 80);
	
	//server = gethostbyname ("api.ipify.org");
	if ((server = gethostbyname ("ipinfo.io")) == NULL)
	{
		fprintf (stderr, "Error in Internet Connection or DNS settings\n");
		exit (EXIT_FAILURE);
	}
	
	memcpy (&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

	if (connect(sock_d, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
	{
		perror ("Internet Connection issue: Check !");
		exit (EXIT_FAILURE);
	}
	
	if (send (sock_d, msgp, strlen(msgp), 0) == -1)
	{
		perror ("ERROR communicating ipinfo.io\n");
		exit (EXIT_FAILURE);
	}
	
	recv (sock_d, rcvmsgp, 512, 0);
	
	//printf ("What I've got : %s\n", rcvmsgp);
	
	web_len = strlen (rcvmsgp);
	pars_len = strlen (parse_wd);
	
	for (web_cnt = 0; web_cnt <= web_len - pars_len; web_cnt++)
	{
		pos = e = web_cnt;
		
		for(pars_cnt = 0; pars_cnt < pars_len; pars_cnt++)
		{
			if (parse_wd [pars_cnt] == rcvmsgp [e])
			{
				e++;
			}
			else
			{
				break;
			}
				
		}
		if( pars_cnt == pars_len)
		{
			break;
		}
	}
	
	//printf ("Position I'm searching is at : %d\n", (pos + pars_len));
	
	struct lon_lat curr_lolt;
	
	for (i = (pos + pars_len); i < (pos + pars_len + 7); i++)
	{
		lat[j] = rcvmsgp[i];
		j++;

	}
	
	j = 0;
	
	printf ("\nOutput lat(str) = %s\n", lat);
	
	curr_lolt.curr_lat = atof(lat);
	
	//printf ("Current Latitude %1.4f\n", curr_lolt.curr_lat);
	
	for (i = (i+1); i < (pos + pars_len + 14); i++)
	{
		lon[j] = rcvmsgp[i];
		j++;
		
	}
	
	printf ("\nOutput lon(str) = %s\n", lon);
	
	curr_lolt.curr_long = atof(lon);
	
	//printf ("Current Longitude %1.4f\n", curr_lolt.curr_long);
	
	return curr_lolt;
	
}
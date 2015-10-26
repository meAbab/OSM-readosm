/*
files that work on this part are -
split_osm.c / nodeANDway.h / searched_file_create.c / only_node_parse.c / nd_ref_faster.c / tag_find_node.c / parse_main.c
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "nodeANDway.h"

char user_search_input[32];

void configureprogram()
{
	int split_ret, nd_ref_ret;
	int wayfile_ret;
	FILE *confFILE, *outputFILE;
	char serTag[32];
	char *extension = ".osm";
	
	
	split_ret = splitOSM();
	
	if (split_ret != 11)
	{
		fprintf (stderr, "ERROR SPLITING OSM FILE\n");
	}
	if (split_ret == 11)
	{
		printf ("spliting Success !!!\n\n");
	}
	
	confFILE = fopen ("prog.conf", "r");

	while( fgets(serTag, sizeof(serTag), confFILE) != NULL)
	{	
		strcpy (user_search_input, strtok(serTag, "$"));
		
		// first delete if there has any temp.txt file then run this.
		
		if (access("temp.txt", F_OK) !=-1 )
			remove ("temp.txt");
		
		wayfile_ret = wayfile2temp (user_search_input);
		
			if (wayfile_ret == 67)
			{
	
				printf ("WAY extraction started for %s !!\n\n", user_search_input);
			
			}
		
		tag_find_node (user_search_input);
		
		nd_ref_faster ();
		
		char filename[strlen (user_search_input) + strlen (extension) + 3];
		
		snprintf (filename, sizeof(filename), "%s%s", user_search_input, extension);
	
			if (access (filename, F_OK) != -1) 
			{
				printf ("\nFinalizing %s file..\n",filename );
				outputFILE = fopen (filename, "a");
				fputs ("</osm>", outputFILE);
				fclose (outputFILE);
			}
			
	}
	
	if (wayfile_ret == 67)
	{
		printf ("WAY extraction finished according conf file !!\n");
	}
	
}

void printmorething()
{
	printf ("Here something more !\n");
}

void helpprinting()
{
	printf ("printing all help issues\n");
}

main()
{
	clock_t begin, tend;
	double ex_time;
	
	
	int menu;
	
	printf (" MENU: \n");
	printf ("1. Configure the Program.\n");
	printf ("2. Run the program.\n");
	printf ("3. Help.\n");
	printf ("Enter your choice: ");
	scanf("%d", &menu);
	
	begin = clock();
	switch (menu)
	{
		case 1: 
		//	printf ("Spliting main big .OSM file.");
			configureprogram();
			break;
		
		case 2:
			printmorething();
			break;
			
		case 3:
			helpprinting();
			break;
			
		default:
			printf ("Please choose from menu.\n");
			break;
	}
		
	tend = clock();
	ex_time = (double)(tend - begin) / CLOCKS_PER_SEC;
	
	printf("\n Execution Time %f\n",ex_time);
	return 0;
}
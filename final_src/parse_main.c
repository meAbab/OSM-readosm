/*
files that work on this part are -
split_osm.c / nodeANDway.h / searched_file_create.c / only_node_parse.c / nd_ref_faster.c / tag_find_node.c / parse_main.c
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "nodeANDway.h"

void configureprogram();
void configupdate ();
void runProgram();
void helpprinting();

char user_search_input[32];

/*
void loopmain()
{
	main();
}
*/

int 
main()
{
	clock_t begin, tend;
	double ex_time;
	
	int menu;
	
	system ("clear");
	
	printf (" MENU: \n");
	printf ("1. Configure the Program.\n");
	printf ("2. Edit / Update config file.\n");
	printf ("3. Run the program.\n");
	printf ("4. Help.\n");
	printf ("5. Quit Program.\n");
	printf ("Enter your choice: ");

	begin = clock();
		
	scanf("%d", &menu);
	
	  switch (menu)
	  {
		  case 1: 
		  //	printf ("Spliting main big .OSM file.");
			  configureprogram();
			  break;
		
		  case 2:
			  configupdate();
			  break;
		
		  case 3:
		      runProgram();
			  break;
			
		  case 4:
			  helpprinting();
			  break;
			 
		  case 5:
			  break;
			
		  /*default:
			  loopmain();
			  break;
			*/  
	    }
	 
	
	tend = clock();
	ex_time = (double)(tend - begin) / CLOCKS_PER_SEC;
	
	printf("\n Execution Time %f\n",ex_time);
	return 0;
}

void configureprogram()
{
	int split_ret, wayfile_ret, tag_find_ret, nd_ref_ret;
	FILE *confFILE, *outputFILE;
	char serTag[32];
	char *extension = ".osm";
	
	// checking whether these files already configured or not
	
	if ( access ("file.desc", F_OK) != 0 )
	{
		FILE *openfileDESC = fopen ("file.desc", "w");
		
		fclose (openfileDESC);
	}
	
	if ( file_check() == 1373)
	{
		
		split_ret = splitOSM();
		
		if (split_ret != 11)
		{
			fprintf (stderr, "ERROR SPLITING OSM FILE\n");
		}
		if (split_ret == 11)
		{
			printf ("spliting Success !!!\n\n");
		}

	}
	
	confFILE = fopen ("prog.conf", "r");

	while( fgets(serTag, sizeof(serTag), confFILE) != NULL)
	{	

		strcpy (user_search_input, strtok(serTag, "$"));
		
		char filename[strlen (user_search_input) + strlen (extension) + 1];
		
		snprintf (filename, sizeof(filename), "%s%s", 
							user_search_input, extension);
		
		if ( access(filename, F_OK) != 0)
		{
		
		// first delete if there has any temp.txt file then run this.
		
		  printf ("Configuring program for Keyword - %s.", user_search_input);
		
		  if (access("temp.txt", F_OK) != -1 )
		  {
			remove ("temp.txt");
		  }
		
		  wayfile_ret = wayfile2temp (user_search_input);
		
			 if (wayfile_ret != 67)
			 {
				fprintf (stderr, "Error Extracting Way file\n");
			 }
		
		  tag_find_ret = tag_find_node (user_search_input);
		     
			 if (tag_find_ret != 1637)
			 {
				 fprintf (stderr, "Error Extracting from Node File\n");
			 }
		
		  nd_ref_ret = nd_ref_faster ();
			 
			 if (nd_ref_ret != 1367)
			 {
				 fprintf (stderr, "Error creating XML from \"temp.txt.\"\n");
			 }
	
			 if (access (filename, F_OK) != -1) 
			 {
				printf ("\nFinalizing %s file..\n",filename );
				outputFILE = fopen (filename, "a");
				fputs ("</osm>", outputFILE);
				fclose (outputFILE);
			 }
		}
			
	}
	
	if (split_ret + wayfile_ret +
			tag_find_ret + nd_ref_ret == 3082)
	{
		printf ("\tProgram Configured Successfully!!\n");
	}
	
	main();
	
}


void configupdate ()
{
	if ( access ("prog.conf", F_OK) != -1)
	{
		system ("pico prog.conf");
	}
	else{
		
		FILE *createCONF = fopen ("prog.conf","w");
		
		system ("pico prog.conf");
		
		fclose (createCONF);
	}
	
	main();
	
}

void runProgram	()
{
	system ("clear");
	system ("./calc_lon_lat");
}


void helpprinting()
{
	help_menu();
	main ();
}
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "readosm.h"
#include "progrun.h"

//void short_result ()
//{
//	shortest_dist();
//}

void loopmain();

static int print_node 
(const void *user_data, const readosm_node *node)
{
 int j, calc_ret;
 const readosm_tag *tag;
	
	
	calc_ret = calc_lon_lat (node->latitude,
							 node->longitude);
	
	if (calc_ret == 1567)
	{
		printf ("lat = %1.7f", node->latitude);
		printf (" lon = %1.7f\n", node->longitude);
		
		for (j=0; j < node->tag_count; j++)
		{
		
		tag = node->tags + j;
		
		printf ("\t\t<tag k=\"%s\" v=\"%s\" />\n",
								tag->key, tag->value);
		
		}
	
	}
	
    return READOSM_OK;
}


int main()
{
	const void *osm_handle;
	int ret;
	char user_input[32];
	char *extension = ".osm";
	
	printf ("\n\n\tGive your desired search keyword (quit for exit): ");
	
	scanf ("%s", user_input);
	
	if((!strcmp (user_input, "tankstelle") || !strcmp (user_input, "Gasstation") ||
	!strcmp (user_input, "tanken") || !strcmp (user_input, "TANKSTELLE")))
		{
			strcpy (user_input, "fuel");
		}
	
	else if((!strcmp (user_input, "market") || !strcmp (user_input, "grocery") ||
		!strcmp (user_input, "supermarket") || !strcmp (user_input, "lebensmittle")))
		{
			strcpy (user_input, "supermarket");
		}
		
	else if ((!strcmp (user_input, "fast_food") || !strcmp (user_input, "mcdonalds")))
		{
			strcpy (user_input, "fast_food");
		}
	
	else if ((!strcmp (user_input, "hospital") || !strcmp (user_input, "krankenhaus") ||
		 !strcmp (user_input, "doctor")))
		 {
			 strcpy (user_input, "hospital");
		 }
		 
	else if ((!strcmp (user_input, "police") || !strcmp(user_input, "polizei")))
		{
			strcpy (user_input, "police");
		}
		
	else if ((!strcmp (user_input, "restaurant") || !strcmp (user_input, "food") ||
		 !strcmp (user_input, "essen")))
		 {
			 strcpy (user_input, "restaurant");
		 }
	
	else if ((!strcmp (user_input, "quit")))
		 {
			system ("./first_check.o");
			return 0;
		 }
	
	else {
		
		  printf ("\t%s is not configured. Use Edit/Update from menu" \
										" and run configure.\n", user_input);
		
		 }
	
	char filename[strlen (user_input) + strlen (extension) + 1];
	
	snprintf (filename, sizeof(filename),
				"%s%s", user_input, extension);
	
	if ( access (filename, F_OK) != 0)
	{
	    printf ("\n%s file not found. Please Edit \"prog.conf\" file and run configure.\n", filename);
		
		return -1;
	}
	
	ret = readosm_open (filename, &osm_handle);
	
	if(ret != READOSM_OK)
	{
		fprintf(stderr, "Unable to open file %d\n", ret);
		goto stop;
	}
	
	ret = readosm_parse(osm_handle, &user_input, print_node, NULL, NULL);
	
	if(ret != READOSM_OK)
	{
		fprintf(stderr, "Parsing error: %d\n", ret);
		goto stop;
	}
	
	short_dist ();
	
	sleep (5);
	
	loopmain ();
	
	stop:
	readosm_close(osm_handle);
	return 0;
}


void loopmain()
{
	system ("clear");
	main ();
}

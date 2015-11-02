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

struct shorted_object
{
	char object_name[128], street_value[128];
	char housenr_value[8], city_value[32];
};

struct shorted_object short_obj_res;

double st_dist=20020;

static const readosm_tag *
find_tag (const readosm_node * node, const char * key)
{
	 int i;
     const readosm_tag *tag;

     for (i = 0; i < node->tag_count; i++)
     {
         tag = node->tags + i;
         if (strcmp(tag->key, key) == 0)
             return tag;
     }
     return NULL;
}

static int print_node 
(const void *user_data, const readosm_node *node)
{
	
 int j;
 char object_name[128];
 double calc_ret = 0.00000;
 
 const readosm_tag *tag;
 const readosm_tag *city;
 const readosm_tag *street;
 const readosm_tag *housenr;
	
	
	calc_ret = calc_lon_lat (node->latitude,
								node->longitude);
	
	
	if (abs (calc_ret) > 0 && abs (calc_ret) < 30000)
	{
	//	printf ("lat = %1.7f", node->latitude);
	//	printf (" lon = %1.7f\n", node->longitude);
	
		printf ("Distance: %f\n", calc_ret);
		
		for (j=0; j < node->tag_count; j++)
		{
		
		  tag = node->tags + j;
		
		  if (strcmp(tag->key,"name") == 0)
		  {
				
			strncpy (object_name,tag->value,128); 
				
		  }
		
		  city = find_tag (node, "addr:city");
		  street = find_tag (node, "addr:street");
		  housenr = find_tag (node, "addr:housenumber");
		
		}

		printf ("Name: %s\n\t\tAT: %s %s, %s\n", 
						object_name, street->value, housenr->value, city->value);
	
	}
	
	if ( calc_ret < st_dist && abs(calc_ret) > 0)
	{
		
		//printf ("\nTHIS IS SHORTEST");
		strncpy (short_obj_res.object_name, object_name, 128);
		strncpy (short_obj_res.street_value, street->value, 128);
		strncpy (short_obj_res.housenr_value, housenr->value, 8);
		strncpy (short_obj_res.city_value, city->value, 32);
		
		st_dist = calc_ret;
		
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
	
	printf ("Name: %s\n\t\tAT: %s %s, %s\n",
				short_obj_res.object_name, short_obj_res.street_value,
				short_obj_res. housenr_value, short_obj_res.city_value);
	//sleep (5);
	
	//loopmain ();
	
	stop:
	readosm_close(osm_handle);
	return 0;
}


void loopmain()
{
	system ("clear");
	main ();
}

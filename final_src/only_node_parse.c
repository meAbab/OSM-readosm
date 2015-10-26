/*
files that work on this part are -
split_osm.c / nodeANDway.h / searched_file_create.c / only_node_parse.c / nd_ref_faster.c / tag_find_node.c / parse_main.c
*/


/* 
/ parsing way for long & lat of respective "nd ref"
*/

#include <stdio.h>
#include "readosm.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "readosm.h"
#include <unistd.h>
#include "nodeANDway.h"

FILE *tempo;

char *special_name_replace 
(char *s, char ser, char rep)  
{
  char *p1;
 
  for (p1=s; *p1; p1++) 
  {
    if (*p1 == ser)
	{
      *p1 = rep;
    }
  }
  return s;
}

static const readosm_tag *
find_tag (const readosm_way * way, const char *key)
{
     int i;
     const readosm_tag *tag;

     for (i = 0; i < way->tag_count; i++)
     {
         tag = way->tags + i;
         if (strcmp(tag->key, key) == 0)
             return tag;
     }
     return NULL;
}

static int 
print_way (const void *user_data, const readosm_way * way)

{
	
	char *way_extract = NULL;	
    char buf[128];
	char *object_name_tmp;
	char object_name[128];
	object_name[0] = 0;
    int i;
	
	const readosm_tag *tag;
	const readosm_tag *city;
	const readosm_tag *street;
	const readosm_tag *housenr;

		 for (i = 0; i < way->tag_count; i++)
            {
				/* we'll now print each <tag> for this way */
                tag = way->tags + i;
			
				if(strcmp(tag->key,"name") == 0)
				{	
					strncpy (buf, tag->value, 128);
					
					object_name_tmp = special_name_replace (buf, '&', 'u');
					object_name_tmp = special_name_replace (object_name_tmp, '"', '-');
					
					strncpy(object_name, object_name_tmp,128); 
				
				}

				if(strcmp(tag->value, user_data) == 0 &&
					object_name[0] != 0) 
				{
					if (way->tag_count > 0)
					{
							city = find_tag(way, "addr:city");
							street = find_tag(way, "addr:street");
							housenr = find_tag(way, "addr:housenumber");
					
					sprintf (buf, "%lld", *(way->node_refs + i));
					
					}
					if(city != NULL && street != NULL && housenr != NULL)
					   {
						
							way_extract = malloc(sizeof(*way_extract) * (7 + strlen (buf) +
												strlen (tag->value) +
												strlen (object_name) + strlen (city->value) +
												strlen (street->value) + strlen (housenr->value)));
							sprintf (way_extract,"%s=%s=%s=%s=%s=%s\n",
												buf, tag->value, object_name, city->value, street->value, housenr->value);
							
							//printf ("%s", way_extract);
						
								fputs (way_extract,tempo);
						
							free (way_extract);
						
						}
					
				}
			
            }
    	
	return READOSM_OK;
}

int parsewayfileonly (char *ptag)
{
	const void *osm_handle;
	char parsesearchtag[32];
	int ret;

	strcpy (parsesearchtag, ptag);
	
	ret = readosm_open ("split_way.osm", &osm_handle);
	
    if (ret != READOSM_OK)
    {
        fprintf (stderr, "OPEN error: %d\n", ret);
        goto stop;
    }
	ret = readosm_parse (osm_handle, parsesearchtag, NULL, print_way,NULL);
	
	if (ret != READOSM_OK)
	{
		fprintf (stderr, "PARSE error: %d\n", ret);
		goto stop;
	}
	
	stop:
    readosm_close (osm_handle);
    
	return 0;
}

int wayfile2temp(char conf_in[])
//int main (int argc, char *argv[])
{
	tempo = fopen ("temp.txt", "a");
	
	parsewayfileonly (conf_in);
		
	fclose (tempo);
	return 67;
}
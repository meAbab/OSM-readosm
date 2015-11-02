/*
files that work on this part are -
split_osm.c / nodeANDway.h / searched_file_create.c / only_node_parse.c / nd_ref_faster.c / tag_find_node.c / parse_main.c
*/

#include <stdio.h>
#include "readosm.h"
#include<stdlib.h>
#include<string.h>
#include "nodeANDway.h"
#include<math.h>

//#include "audlolt.h"

int count = 0;

char *special_n_replace 
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
find_tag (const readosm_node * node, const char *key)
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

static int
print_node (const void *user_data, const readosm_node *node)
{
	
 char *object_name_tmp;
 char object_name[128];
 object_name[0] = 0;

 const readosm_tag *tag;
 const readosm_tag *city;
 const readosm_tag *street;
 const readosm_tag *housenr;
	 
 int j;
 char nodeid[128];

	for (j = 0; j < node->tag_count; j++)
	{	
		tag = node->tags + j;	
		
		//Taking the name of the object to finally figure which object is nearer. 
		//Need to make this if condition with tag->key as priority, first name
		
			if(strcmp(tag->key,"name") == 0)
			{
				//	strcpy(object_name,tag->value);  object_name = tag->value;
				strncpy (nodeid, tag->value, 128);
					
				object_name_tmp = special_n_replace 
									(nodeid, '&', 'u');
				object_name_tmp = special_n_replace 
									(object_name_tmp, '"', '-');
					
				strncpy(object_name, object_name_tmp,128); 
			}
				// comparing given argument string, to result only those object
		
			if(strcmp(tag->value, user_data) == 0 &&
				object_name[0] != 0) 
				{	
				if (node->tag_count > 0)
					{		
							    city = find_tag(node, "addr:city");
								street = find_tag(node, "addr:street");
								housenr = find_tag(node, "addr:housenumber");

							if (city == NULL && street == NULL && housenr == NULL)
								return READOSM_OK;

							count++;
					}

					if(city != NULL && street != NULL && housenr != NULL)
					{
						snprintf(nodeid,128,"%lld",node->id);
						
/*						 calculating function is defined in searched_file_create.c */
						
						calculating(nodeid, node->latitude,
								node->longitude, object_name,
								city->value,
								street->value, housenr->value);
						
					}
					
				}
			
	}
    return READOSM_OK;
}



int tag_find_node(char tag_find[])
//int main (int argc, char *argv[])
{
	const void *osm_handle;
	int ret;
		
	//printf (" %s\n", tag_find);
	
	ret = readosm_open("node_split.osm", &osm_handle);
	if(ret != READOSM_OK)
	{
		fprintf(stderr, "Unable to open file %d\n", ret);
		goto stop;
	}

	ret = readosm_parse(osm_handle, tag_find, print_node, NULL, NULL);

	if(ret != READOSM_OK)
	{
		fprintf(stderr, "Parsing error: %d\n", ret);
		goto stop;
	}

	stop:
	readosm_close(osm_handle);
	return 1637;
}
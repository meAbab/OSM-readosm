/*
files that work on this part are -
split_osm.c / nodeANDway.h / searched_file_create.c / only_node_parse.c / nd_ref_faster.c / tag_find_node.c / parse_main.c
*/

#include <stdio.h>
#include "readosm.h"
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include "nodeANDway.h"
#define BUF_SIZE ( 256 )

char user_search_input[32];

struct ref_at_way
{
	double ndref;
	char *type, *name, *city, *street, *housenr;
};


static int print_node (const void *user_data, const readosm_node *node)
{
	char nodeid[32];
	struct ref_at_way *handle_user_data = (struct ref_at_way *) user_data;
		
				if(node->id == handle_user_data->ndref)
				{
					
					sprintf(nodeid,"%1.0f",handle_user_data->ndref);
					
					calculating (nodeid, node->latitude,
								node->longitude, handle_user_data->name,
								handle_user_data->city,
								handle_user_data->street, handle_user_data->housenr);
								
				}
		 
return READOSM_OK;
}

int ndref2lonlat(struct ref_at_way ndref1)
{
	const void *osm_handle;
	int ret;
	
	ret = readosm_open ("node_split.osm", &osm_handle);
	
	if (ret != READOSM_OK)
      {
          fprintf (stderr, "OPEN error: %d\n", ret);
          goto stop;
      }

	ret = readosm_parse (osm_handle, &ndref1, print_node, NULL,NULL);
	
	if (ret != READOSM_OK)
      {
          fprintf (stderr, "PARSE error: %d\n", ret);
          goto stop;
      }
	  		
  stop:
    readosm_close (osm_handle);

		return 0;
}
int nd_ref_faster()
//int main ()
{
	
	FILE *confFILE;
	char *searchtag;
	char serTag[BUF_SIZE];
	
	struct ref_at_way way_obj;
	
	confFILE = fopen("temp.txt", "r");
	
	while( fgets(serTag, sizeof(serTag), confFILE) != NULL)
	{
		char *newline;
		if((newline = strchr (serTag, '\n')) != NULL)
			*newline = '\0';
		
		searchtag = strtok(serTag, "=" );
		
		way_obj.ndref = atof(searchtag);
		way_obj.type = strtok (NULL,"=");
		way_obj.name = strtok (NULL, "=");
		way_obj.city = strtok (NULL, "=");
		way_obj.street = strtok (NULL, "=");
		way_obj.housenr = strtok (NULL, "=");

		strcpy (user_search_input , way_obj.type);
		
		ndref2lonlat(way_obj);
	}
			
	fclose(confFILE);

	return 1367;
}
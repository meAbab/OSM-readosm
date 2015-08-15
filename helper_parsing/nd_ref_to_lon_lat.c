#include <stdio.h>
#include "readosm.h"
#include<string.h>
#include<stdlib.h>
#include "nodeANDway.h"

int j = 0;
struct ref_at_way 
{
	int ndref;
};
static int print_node (const void *user_data, const readosm_node *node)
{
const readosm_tag *tag;
struct ref_at_way *handle_user_data = (struct ref_at_way *) user_data;
				if(j > 0)
				{ 	j = 0;
					return READOSM_OK;
				}
				if(node->id == handle_user_data->ndref){
					printf (" lat=\"%1.7f\"", node->latitude);
					printf (" lon=\"%1.7f\"\n", node->longitude);
					j = j+1;
				}

return READOSM_OK;
}

int lon_lat_node_parse (int in_ndref)
{
    const void *osm_handle;
    int ret;
	struct ref_at_way ndref1;
	ndref1.ndref = in_ndref;
    
    ret = readosm_open ("Kiel.osm", &osm_handle);
	//ret = readosm_open (argv[1], &osm_handle);
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
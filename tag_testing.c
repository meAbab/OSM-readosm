#include <stdio.h>
#include "readosm.h"

//lng (min/max): 9.63621043828/10.6304495617 lat (min/max): 54.0434449275/54.6231550725

static int print_node (const void *user_data, const readosm_node *node)
{
char buf[128];
int i,j;
const readosm_tag *tag;

for (j=0; j < node->tag_count; j++)
{
	tag = node->tags + j;
	if(strcmp(tag->value, "fuel") == 0) {
		
		if (node->tag_count > 0){

			sprintf(buf, "%lld", node->id);
			printf("\t<node id=\"%s\"",buf);

			if (node->latitude != READOSM_UNDEFINED)
				printf (" lat=\"%1.7f\"", node->latitude);
			if (node->longitude != READOSM_UNDEFINED)
				printf (" lon=\"%1.7f\"", node->longitude);
				printf (" />\n");
	
				for (i = 0; i < node->tag_count; i++)
					{
						tag = node->tags + i;
						printf ("\t\t<tag k=\"%s\" v=\"%s\" />\n", tag->key,tag->value);
					}
				printf ("\t</node>\n");
			}
		}
	}

    return READOSM_OK;
}

int main(int argc, char *argv[])
{
	const void *osm_handle;
	int ret;
		
	if(argc !=2)
	{
		fprintf(stderr, "Usage: tag_testing path-to-OSM-file\n");
		return -1;
	}
	ret = readosm_open(argv[1], &osm_handle);
	if(ret != READOSM_OK)
	{
		fprintf(stderr, "Unable to open file %d\n", ret);
		goto stop;
	}
	
	ret = readosm_parse(osm_handle, (const void *) 0,print_node, NULL, NULL);
	
	if(ret != READOSM_OK)
	{
		fprintf(stderr, "Parsing error: %d\n", ret);
		goto stop;
	}
	stop:
	readosm_close(osm_handle);
	return 0;
}
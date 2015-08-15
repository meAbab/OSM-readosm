/* 
/ parsing way for long & lat of respective "nd ref"
*/
#include <stdio.h>
#include "readosm.h"
#include<string.h>
#include "nodeANDway.h"

int numberofTags=0;
static int
print_way (const void *user_data, const readosm_way * way)
{
    char buf[128];
    int i;
    const readosm_tag *tag;
        sprintf (buf, "%lld", way->id);
		 for (i = 0; i < way->tag_count; i++)
            {
				/* we'll now print each <tag> for this way */
                tag = way->tags + i;
				if(strcmp(tag->value, "supermarket") == 0) 
				{
					printf ("\t<way id=\"%s\"", buf);
					printf ("\t\t<tag k=\"%s\" v=\"%s\" />\n", tag->key, tag->value);
					sprintf (buf, "%lld", *(way->node_refs + i));
					printf ("\t\t<nd ref=\"%s\" />\n", buf);
					lon_lat_node_parse(*(way->node_refs + i));
				}
            }
    return READOSM_OK;
}


int main (int argc, char *argv[])
{
    const void *osm_handle;
    int ret,n;
    if (argc != 2)
      {
          fprintf (stderr, "usage: test_osm1 path-to-OSM-file\n");
          return -1;
      }

    ret = readosm_open (argv[1], &osm_handle);
    if (ret != READOSM_OK)
      {
          fprintf (stderr, "OPEN error: %d\n", ret);
          goto stop;
      }
	ret = readosm_parse (osm_handle, (const void *) 0, NULL, print_way,NULL);
    if (ret != READOSM_OK)
      {
          fprintf (stderr, "PARSE error: %d\n", ret);
          goto stop;
      }
    fprintf (stderr, "Ok, OSM input file successfully parsed\n");
  stop:
    readosm_close (osm_handle);
    return 0;
}
/*
files that work on this part are -
split_osm.c / nodeANDway.h / searched_file_create.c / only_node_parse.c / nd_ref_faster.c / tag_find_node.c / parse_main.c
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "nodeANDway.h"
#include "readosm.h"


char *file_header="<osm version=\"0.6\" generator=\"osmconvert 0.8.3\">\n";
char *first_line = "<node id=\"\" lat=\"\" lon=\"\">\n";
char *second_line = "<tag k=\"name\" v=\"\"/>\n";
char *third_line  = "<tag k=\"addr:city\" v=\"\"/>\n";
char *fourth_line = "<tag k=\"addr:street\" v=\"\"/>\n";
char *fifth_line = "<tag k=\"addr:housenumber\" v=\"\"/>\n";
char *node_close = "</node>\n";

int onetime = 0;


int calculating(char *nodeid, double node_lat,
				double node_long, const char *objvl,
				const char *cityvl,
				const char *streetvl, const char *housenrvl)
{

	char *a;
	char *spnt_temp_all = NULL;
	a = user_search_input;
	char *extension = ".osm";
	char fileSpec [strlen (a) + strlen (extension) + 3];
	FILE *indexfile;
	
	snprintf (fileSpec, sizeof (fileSpec), "%s%s", a, extension);
	
	if (access (fileSpec, F_OK) != 0 )
	{
		onetime = 0;

	}

	indexfile = fopen(fileSpec,"a");
						
		if (onetime == 0)
		{
			spnt_temp_all = malloc(sizeof(*spnt_temp_all) * (128 + strlen(file_header) +
									strlen(first_line)  +
									strlen(nodeid)      +
									strlen(second_line) +
									strlen(objvl)		  +
									strlen(third_line)  +
									strlen(cityvl)	  +
									strlen(fourth_line) +
									strlen(streetvl)  +
									strlen(fifth_line)  +
									strlen(housenrvl)	  +
									strlen(node_close)));
		if(indexfile != NULL)
		{	
							sprintf(spnt_temp_all,
							"<osm version=\"0.6\" generator=\"osmconvert 0.8.3\">\n"
							" <node id=\"%s\" lat=\"%1.5f\" lon=\"%1.5f\">\n"
							"  <tag k=\"name\" v=\"%s\"/>\n"
							"  <tag k=\"addr:city\" v=\"%s\"/>\n"
							"  <tag k=\"addr:street\" v=\"%s\"/>\n"
							"  <tag k=\"addr:housenumber\" v=\"%s\"/>\n"
							" </node>\n",nodeid,node_lat,node_long,objvl,cityvl,streetvl,housenrvl);
							}
						fputs(spnt_temp_all,indexfile);
						
						free(spnt_temp_all);
						//printf("\nworkding\n");
						fclose(indexfile);
						onetime++;
		}
		
		else {
								
			spnt_temp_all = malloc(sizeof(*spnt_temp_all) * (128 +
									strlen(first_line)  +
									strlen(nodeid)     +
									strlen(second_line) +
									strlen(objvl)		  +
									strlen(third_line)  +
									strlen(cityvl)	  +
									strlen(fourth_line) +
									strlen(streetvl)  +
									strlen(fifth_line)  +
									strlen(housenrvl)	  +
									strlen(node_close)));
														  
		if(indexfile != NULL)
		{	
								sprintf(spnt_temp_all,
								" <node id=\"%s\" lat=\"%1.5f\" lon=\"%1.5f\">\n"
								"  <tag k=\"name\" v=\"%s\"/>\n"
								"  <tag k=\"addr:city\" v=\"%s\"/>\n"
								"  <tag k=\"addr:street\" v=\"%s\"/>\n"
								"  <tag k=\"addr:housenumber\" v=\"%s\"/>\n"
								" </node>\n",nodeid,node_lat,node_long,objvl,cityvl,streetvl,housenrvl);
								}
						fputs(spnt_temp_all,indexfile);
									
						free(spnt_temp_all);
						fclose(indexfile);
									
		}
		
	return 0;				
}
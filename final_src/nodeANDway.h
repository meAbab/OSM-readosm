/*
files that work on this part are -
split_osm.c / nodeANDway.h / searched_file_create.c / only_node_parse.c / nd_ref_faster.c / tag_find_node.c / parse_main.c
*/

#ifndef _nodeANDway_H_
#define _nodeANDway_H_

extern int lon_lat_node_parse (int in_ndref, char tag_value[]);

extern int calculating
		(char *nodeid, double node_lat,
		double node_long, const char *objvl,
		const char *cityvl,
		const char *streetvl, const char *housenrvl);
	
int splitOSM();

int wayfile2temp(char conf_in[]);

int tag_find_node(char tag_find[]);

int nd_ref_faster();

extern double curr_long,curr_lat,shortest_dist;
extern char nearest_object[128];
extern int no_of_entry;

extern char user_search_input[32];

#endif
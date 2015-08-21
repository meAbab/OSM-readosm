#ifndef _nodeANDway_H_
#define _nodeANDway_H_

extern int lon_lat_node_parse (int in_ndref);
extern int calculation(double node_lat, double node_long, char value[]);
extern double curr_long,curr_lat,shortest_dist;
extern char nearest_object[128];
extern int no_of_entry;

#endif
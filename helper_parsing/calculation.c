#include<stdio.h>
#include<math.h>
#include<string.h>
#include "nodeANDway.h"

double deg2rad(double lat);
double dist_2_po,dist_lon, dist_lat,deg_calc;
int eRadius = 12742000;;

int calculation(double node_lat, double node_long, char value[])
{
							printf (" lat=\"%1.7f\"", node_lat);
							printf (" lon=\"%1.7f\"", node_long);
							printf (" Name = %s\n", value);
							no_of_entry = no_of_entry +1;
							
							//two point distance calculation
							if(curr_long > node_long)
							{
								dist_lon = deg2rad(curr_long) - deg2rad(node_long);
							}else{
								dist_lon = deg2rad(node_long) - deg2rad(curr_long);
							}
							if(curr_lat > node_lat)
							{
								dist_lat = deg2rad(curr_lat) - deg2rad(node_lat);
							}else{
								dist_lat = deg2rad(node_lat) - deg2rad(curr_lat);
							}
							deg_calc = ((1 - cos(dist_lat)) + (1 - cos(dist_lon)) * cos(deg2rad(curr_lat)) * cos(deg2rad(node_lat)));
							deg_calc = deg_calc/2;
							dist_2_po = eRadius * asin(sqrt(deg_calc));
							//brute_force_sorting - better algorithm will carry less cost
							if(dist_2_po < shortest_dist)
							{
								shortest_dist = dist_2_po;
								strcpy(nearest_object,value);
							}
}

double deg2rad(double lat)
	{
		return 0.0174532925*lat;
	}
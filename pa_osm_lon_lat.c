// This program is on-going dev process. 

#include <stdio.h>
#include "readosm.h"
#include<stdlib.h>
#include<string.h>
#include<math.h>
int no_of_entry=0;
double curr_long=10.13625,curr_lat = 54.32168,shortest_dist=20020; // highest distance between two point in earth is 20020 km
double deg2rad(double lat);
char nearest_object[128];

// struct to calculate maximum and minimum long & lat for given radius kilometres. the char arg is for storing given argument in main function
struct arg_max_min_lo_lt
{
	double min_long;
	double min_lat;
	double max_long;
	double max_lat;
	char arg[50];
};	

// calculating maximum & minimum long & lat for given radius kilometres.
struct arg_max_min_lo_lt get_lo_lt_values()
{
		int eRadius = 12742;
		float radius=5;
		struct arg_max_min_lo_lt m_lo_lt_ptr;
		//each degree of lon or lat is approximately 69 miles or 111 kilometres difference
		double denominator = cos(deg2rad(curr_lat)) * 111;
		m_lo_lt_ptr.min_long = curr_long - (radius / denominator );
		m_lo_lt_ptr.max_long = curr_long + (radius / denominator );
		m_lo_lt_ptr.min_lat = curr_lat - (double)radius / 111;
		m_lo_lt_ptr.max_lat = curr_lat + (double)radius / 111;
		return m_lo_lt_ptr;
}

static int print_node (const void *user_data, const readosm_node *node)
{
char object_name[128];
int i,j,eRadius = 12742000;
const readosm_tag *tag;
double dist_lon, dist_lat,deg_calc,dist_2_po;
struct arg_max_min_lo_lt *handle_user_data = (struct arg_max_min_lo_lt *) user_data;

	for (j=0; j < node->tag_count; j++)
	{
		tag = node->tags + j;
		//Taking the name of the object to finally figure which object is nearer. 
		if(strcmp(tag->key,"name") == 0)
		{	strcpy(object_name,tag->value);	}
	// comparing given argument string, to result only those object
			if(strcmp(tag->value, handle_user_data->arg) == 0) 
				{
		
				if (node->tag_count > 0)
					{
				
//				if (node->latitude != READOSM_UNDEFINED && node->latitude <= 54.366725045 && node->latitude >= 54.276634955 && node->longitude != READOSM_UNDEFINED && node->longitude <= 10.213483244 && node->longitude >= 10.059016756) 
					//	condition here is if long AND lat is less_than_equal of MAX or more_than_equal of MIN
					if (node->latitude != READOSM_UNDEFINED && node->latitude <= handle_user_data->max_lat && node->latitude >= handle_user_data->min_lat && node->longitude != READOSM_UNDEFINED && node->longitude <= handle_user_data->max_long && node->longitude >= handle_user_data->min_long) 
						{
							printf (" lat=\"%1.7f\"", node->latitude);
							printf (" lon=\"%1.7f\"", node->longitude);
							printf ("\t\t<tag k=\"%s\" v=\"%s\" />\n", tag->key,tag->value);
							//printf ("\t\t<tag k=\"%s\" v=\"%s\" />\n",)
							no_of_entry = no_of_entry +1;
							
							//two point distance calculation
							if(curr_long > node->longitude)
							{
								dist_lon = deg2rad(curr_long) - deg2rad(node->longitude);
							}else{
								dist_lon = deg2rad(node->longitude) - deg2rad(curr_long);
							}
							if(curr_lat > node->latitude)
							{
								dist_lat = deg2rad(curr_lat) - deg2rad(node->latitude);
							}else{
								dist_lat = deg2rad(node->latitude) - deg2rad(curr_lat);
							}
							deg_calc = ((1 - cos(dist_lat)) + (1 - cos(dist_lon)) * cos(deg2rad(curr_lat)) * cos(deg2rad(node->latitude)));
							deg_calc = deg_calc/2;
							dist_2_po = eRadius * asin(sqrt(deg_calc));
							//brute_force_sorting - better algorithm will carry less cost
							if(dist_2_po < shortest_dist)
							{
								shortest_dist = dist_2_po;
								strcpy(nearest_object,object_name);
							}
						}
					}
				}
		
	}
    return READOSM_OK;
}

int main(int argc, char** argv)
{
	const void *osm_handle;
	int ret, choice;
	//char arg[50]
	struct arg_max_min_lo_lt arg_and_calc = get_lo_lt_values();
	if(argc !=3)
	{
		fprintf(stderr, "Usage: tag_testing path-to-OSM-file argument\n");
		return -1;
	}
	ret = readosm_open(argv[1], &osm_handle);
	if(ret != READOSM_OK)
	{
		fprintf(stderr, "Unable to open file %d\n", ret);
		goto stop;
	}
	//strcpy(arg,argv[2]);
	strcpy(arg_and_calc.arg,argv[2]);
	// comparing possible search string. but finally will search for fuel, as tankstelle amenity = fuel
	if((!strcmp(arg_and_calc.arg,"tankstelle")||!strcmp(arg_and_calc.arg,"Gasstation")||!strcmp(arg_and_calc.arg,"tanken")||!strcmp(arg_and_calc.arg,"TANKSTELLE")))
	{
		//strcpy(arg,"fuel");
		strcpy(arg_and_calc.arg,"fuel");
	}
	ret = readosm_parse(osm_handle, &arg_and_calc,print_node, NULL, NULL);

	if(ret != READOSM_OK)
	{
		fprintf(stderr, "Parsing error: %d\n", ret);
		goto stop;
	}
	printf("Total Number of Entry found: %d\n",no_of_entry);
	printf("Your nearest %s search result is approximately : %1.7f meter far names %s\n",argv[2],shortest_dist,nearest_object);
	stop:
	readosm_close(osm_handle);
	return 0;
}
// degree to radian.
double deg2rad(double lat)
	{
		return 0.0174532925*lat;
	}

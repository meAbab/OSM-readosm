#include <stdio.h>
#include <math.h>
#include "progrun.h"


struct lon_lat calc_lnlt;
int only_once1 = 0;

double shortest_dist=20020; // highest distance between two point in earth is 20020 km

int count = 0;

double deg2rad(double lat);

void short_dist()
{
	
	if (count == 0)
	{
		printf ("\nNo object found in 3 KM radius\n");
	}
	
	if (shortest_dist < 1000)
	{
		printf ("\n\nYou have %d searched object in 3 KM radius\n", count);
		printf ("\n\nShortest Distance to Object is approx. %f meter\n\n", shortest_dist);
	}
	
	if (shortest_dist > 1000 && count > 0)
	{
		printf ("\n\nYou have %d searched object in 3 KM radius\n", count);
		printf ("\n\nShortest Distance to Object is approx. %1.1f Km\n\n", (shortest_dist / 1000));
	}
	
	
}

struct arg_max_min_lo_lt
{
	double min_long;
	double min_lat;
	double max_long;
	double max_lat;
};	

// calculating maximum & minimum long & lat for given radius kilometres.

struct arg_max_min_lo_lt get_lo_lt_values()
{
	
		float radius= 3;
		
		if(only_once1 == 0)
		{
			calc_lnlt = iptoll();
			only_once1++;
		}
		
		struct arg_max_min_lo_lt m_lo_lt_ptr;

		//each degree of lon or lat is approximately 69 miles or 111 kilometres difference
		
		double denominator = cos(deg2rad(calc_lnlt.curr_lat)) * 111;
		
		m_lo_lt_ptr.min_long = calc_lnlt.curr_long - 
								(radius / denominator );
								
		m_lo_lt_ptr.max_long = calc_lnlt.curr_long + 
								(radius / denominator );
								
		m_lo_lt_ptr.min_lat = calc_lnlt.curr_lat - 
								(double)radius / 111;
								
		m_lo_lt_ptr.max_lat = calc_lnlt.curr_lat + 
								(double)radius / 111;
		
		
		return m_lo_lt_ptr;
		
}


double  
calc_lon_lat(double node_lat, double node_long )
{
	
	int eRadius = 12742000;  // earth diameter = 12742 Km.  calc_ret = 11,
	
	double dist_lon, dist_lat, deg_calc, dist_2_po;
		
	struct arg_max_min_lo_lt short_calc = get_lo_lt_values();
	
	if (node_lat <= short_calc.max_lat && node_lat >= short_calc.min_lat && 
		node_long <= short_calc.max_long && node_long >= short_calc.min_long)
		
	  {
			if(calc_lnlt.curr_long > node_long)
			 {
			   dist_lon = deg2rad(calc_lnlt.curr_long) - deg2rad(node_long);
			 }
			 else{
			   dist_lon = deg2rad(node_long) - deg2rad(calc_lnlt.curr_long);
			 }
			
			if(calc_lnlt.curr_lat > node_lat)
			 {
			   dist_lat = deg2rad(calc_lnlt.curr_lat) - deg2rad(node_lat);
			 }
			 
			 else{
			   dist_lat = deg2rad(node_lat) - deg2rad(calc_lnlt.curr_lat);
			 }
			 
			 deg_calc = ((1 - cos(dist_lat)) + (1 - cos(dist_lon)) * 
							  cos(deg2rad(calc_lnlt.curr_lat)) * cos(deg2rad(node_lat)));
							
			 deg_calc = deg_calc/2;
			 
			 dist_2_po = eRadius * asin(sqrt(deg_calc));

			 
			if(dist_2_po < shortest_dist)
			 {
				shortest_dist = dist_2_po;
			 }
			 
		count++;
		
		//calc_ret = 1567;
	  }
		
	
	return dist_2_po;	
}

double deg2rad(double lat)
	{
		return 0.0174532925*lat;
	}
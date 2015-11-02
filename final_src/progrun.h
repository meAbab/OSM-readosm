#ifndef _progrun_H_
#define _progrun_H_

struct lon_lat{
	double curr_long;
	double curr_lat;
};

double calc_lon_lat(double node_lat, double node_long );

void short_dist();

struct lon_lat iptoll();

#endif
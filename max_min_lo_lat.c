// long & lat of a given area, i.e. 5 km.
#include <stdio.h>
#include <math.h>
double deg2rad(double lat);
int main()
{
int eRadius = 12742;
// current location here is Kiel, Germany.
double curr_long=10.13625,curr_lat = 54.32168,cox_calc,dLon,dLat,cir,orig_distance;
float radius=5;
//each degree of lon or lat is approximately 69 miles or 111 kilometres difference
// as it's not exactly 111 kilometres so you'll not get precision distance here.
double denominator = cos(deg2rad(curr_lat)) * 111;
double min_long = curr_long - (radius / denominator );
double max_long = curr_long + (radius / denominator );
double min_lat = curr_lat - (double)radius / 111;
double max_lat = curr_lat + (double)radius / 111;
printf("Minimum Longitude :%1.9f\nMaximum Longitude: %1.9f\n",min_long,max_long);
printf("Minimum Latitude :%1.9f\nMaximum Latitude: %1.9f\n",min_lat,max_lat);
//used haversine formula
dLon = deg2rad(max_long)- deg2rad(min_long);
dLat = deg2rad(max_lat) - deg2rad(min_lat);
cox_calc = ((1 - cos(dLat)) + (1 - cos(dLon)) * cos(deg2rad(min_lat)) * cos(deg2rad(max_lat)));
cox_calc = cox_calc / 2;
orig_distance = eRadius * asin(sqrt(cox_calc));
printf("If found, it could be original Distance: %1.7f\n",orig_distance);
return 0;
}

double deg2rad(double lat)
{
	return 0.0174532925*lat;
}
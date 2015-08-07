#include <stdio.h>
#include <math.h>
double deg2rad(double lat);
int main()
{
double curr_long=-2.708077,curr_lat = 53.754842;
int radius=20;
double denominator = cos(deg2rad(curr_lat)) * 69;
double min_long = curr_long - (radius / denominator );
double max_long = curr_long + (radius / denominator );
double min_lat = curr_lat - (double)radius / 69;
double max_lat = curr_lat + (double)radius / 69;
printf("Minimum Longitude :%1.9f\nMaximum Longitude: %1.9f\n",min_long,max_long);
printf("Minimum Latitude :%1.9f\nMaximum Latitude: %1.9f\n",min_lat,max_lat);
return 0;
}

double deg2rad(double lat)
{
	return 0.0174532925*lat;
}
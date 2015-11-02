#include <stdio.h>
#include <string.h>
#include <unistd.h>

//int main()
int file_check()

{
	
	FILE *file_check;
	double file_size;
	double node_file_size = 0, way_file_size = 0, relation_file_size = 0;
	char file_size_str[4], split_file_size[4], *file_size_saved;
	char file_string[256];
	int return_value;
	
	if ((file_check = fopen ("nms.osm", "rb")) != NULL)
	{
		fseek (file_check, 0, SEEK_END);
		file_size = ftell (file_check);
	
		sprintf (file_size_str, "%1.0f", file_size);
	
		fclose (file_check);
	}
	
	if ((file_check = fopen ("nms.osm", "rb")) == NULL)
	{
		
		perror ("MAIN .osm file not available. PROG. EXIT!!!\n");
		return -1;
		
	}
	
	if ((file_check = fopen ("node_split.osm", "rb")) != NULL)
	{
		fseek (file_check, 0, SEEK_END);
		node_file_size = ftell (file_check);
		
		fclose (file_check);
	}
	
	if ((file_check = fopen ("way_split.osm", "rb")) != NULL)
	{
		fseek (file_check, 0, SEEK_END);
		way_file_size = ftell (file_check);
		
		fclose (file_check);
	}
	
	if ((file_check = fopen ("relation_split.osm", "rb")) != NULL)
	{
		fseek (file_check, 0, SEEK_END);
		relation_file_size = ftell (file_check);
		
		fclose (file_check);
	}
	//printf ("Till here\n");
	sprintf (split_file_size, "%1.0f", node_file_size +
										way_file_size +
										relation_file_size);
	
	file_check = fopen ("file.desc", "rb");
	
	while (fgets (file_string, 256, file_check) != NULL)
	{
		file_size_saved = strtok (file_string, "#");
		
		if ( strcmp (file_size_saved, file_size_str) == 0 &&
			access ("node_split.osm", F_OK) != -1 &&
			access ("way_split.osm", F_OK) != -1 &&
			access ("relation_split.osm", F_OK) != -1 &&
			strcmp (file_size_saved, split_file_size) == 0)
		{
			
			return_value = 1327;
			break;
			
		}
		
		break;
	}
	
	if (strcmp (file_size_saved, file_size_str) != 0 ||
		strcmp (file_size_saved, split_file_size) != 0 ||
		access ("node_split.osm", F_OK) != 0 ||
		access ("way_split.osm", F_OK) != 0 ||
		access ("relation_split.osm", F_OK) != 0)
	
	{
		remove ("node_split.osm");
		remove ("way_split.osm");
		remove ("relation_split.osm");
		
		return_value = 1373;
		
	}
	
	fclose (file_check);
	
	return return_value;
	
}
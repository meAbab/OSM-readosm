/*
files that work on this part are -
split_osm.c / nodeANDway.h / searched_file_create.c / only_node_parse.c / nd_ref_faster.c / tag_find_node.c / parse_main.c
*/

/* 
	This file is a modification of 
	hxxp://rosettacode.org/wiki/Read_a_specific_line_from_a_file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//#include "nodeANDway.h"

#define BUF_SIZE ( 256 )
 
char *get_nth_line (FILE *f, int first_line_no, int last_line_no)
{
    char   buf[ BUF_SIZE ];
    size_t curr_alloc = BUF_SIZE, curr_ofs = 0;
    char   *line      = malloc( BUF_SIZE );
    int    in_line    = last_line_no == 1;
    size_t bytes_read;
 
    if ( first_line_no < 1 )
        return NULL;
 
    if ( !line )
        return NULL;
 
    int first_line_no_handler = first_line_no;
	last_line_no = last_line_no + 2 ;
		
  while ( (last_line_no - first_line_no) && 
		  ( bytes_read = fread( buf, 1, BUF_SIZE, f ) ) > 0 )
    {
        int i;
 
        for ( i = 0 ; i < bytes_read ; i++ )
        {
            if ( in_line )
            {
                if ( curr_ofs >= curr_alloc )
                {
                    curr_alloc <<= 1;
                    line = realloc( line, curr_alloc );
 
                    if ( !line )   
                        return NULL;
                }
                line[ curr_ofs++ ] = buf[i];
				
            }
 
            if ( buf[i] == '\n' )	
            {
				 first_line_no_handler--;

				if(first_line_no_handler <= 1)
				{   in_line = 1;
					last_line_no--;
				}

				if ( (last_line_no - first_line_no) == 0)
                    break;
			}
        }
		
    }
 
    if ( (last_line_no - first_line_no) != 0 ) 
    {
        free( line );
        return NULL;
    }
 
    line = realloc( line, curr_ofs + 1 );
 
    if ( !line ) 
        return NULL;
 
    line[ curr_ofs ] = '\0';
 
    return line;
}
 
int splitOSM()
//int main()
{
	
	char begin[50] = "<osm version=\"0.6\" generator=\"osmconvert 0.8.3\">\n";
	//char *line_bw = NULL;
	char end[7] = "</osm>\n";
	FILE *openFP;
	char way_compare[] = "\t<way i";
	FILE *fp;
	char ckchr[8];
	int count_line=1;
	int way_line = 0, z = 0, way_last_line = 0;
	
	if(!(fp = fopen("Kiel.osm", "r")))
	{
		printf("\n Error on OSM file opening\n");
		return -1;
	}
	
	char chr = getc(fp);
	
	while(chr != EOF)
	{
	if(chr == '\n')
		{	count_line++;
			fgets(ckchr, 8, fp);
			if(!strncmp(way_compare,ckchr,8)) 
				{
				z++;
				if(z == 1)
				{
					way_line = count_line;
					strcpy(way_compare,"\t<relat");
				}
				if(z == 2)
					way_last_line = count_line;
				}
		}
		chr = getc(fp);
	}
	
	//printf(" way_start = %d Way Ends = %d Last Line = %d", way_line, way_last_line, count_line);
	
	if(access("node_split.osm", F_OK) != 0 )
	{
		rewind(fp);
		char *line_bw = get_nth_line( fp, 1,
										  way_line-2);
								
		openFP = fopen("node_split.osm", "w");
		if ( line_bw )
			{
				if(openFP != NULL)
				{
					fputs(line_bw,openFP);
					fputs(end,openFP);
				}
				//printf("The line between Text is:\n%s\n", line_bw );
				free( line_bw );
			} 	
		else
			{
				printf("Did not find the lines of input.  Reason:  ");
				if ( feof( stdin ) )
					puts("End of file reached.");
				else if ( ferror( stdin ) )
					puts("Error reading input.");
				else
					puts("Out of memory.");
			}
		fclose(openFP);
	}
	
	if(access("way_split.osm", F_OK) != 0 )
	{
		rewind(fp);
	//	line_bw = NULL;
		
		char *line_bw2 = get_nth_line( fp, way_line,
										way_last_line - 1);	
		openFP = fopen("way_split.osm", "w");
		
		fputs(begin,openFP);
		
		if ( line_bw2 )
			{
				if(openFP != NULL)
				{
					fputs(line_bw2,openFP);
					fputs(end,openFP);
				}
				//printf("The line between Text is:\n%s\n", line_bw );
				free( line_bw2 );
			} 	
		else
			{
				printf("Did not find the lines of input.  Reason:  ");
				if ( feof( stdin ) )
					puts("End of file reached.");
				else if ( ferror( stdin ) )
					puts("Error reading input.");
				else
					puts("Out of memory.");
			}
		fclose(openFP);
	}
	
	if(access("relation_split.osm", F_OK) != 0 )
	{
		rewind(fp);
		
		char *line_bw3 = get_nth_line( fp, way_last_line,
										count_line - 1);
		
		openFP = fopen("relation_split.osm", "w");
		
		fputs(begin,openFP);
		
		if ( line_bw3 )
			{
				if(openFP != NULL)
				{
					fputs(line_bw3,openFP);
					fputs(end,openFP);
				}
				//printf("The line between Text is:\n%s\n", line_bw );
				free( line_bw3 );
			} 	
		else
			{
				printf("Did not find the lines of input.  Reason:  ");
				if ( feof( stdin ) )
					puts("End of file reached.");
				else if ( ferror( stdin ) )
					puts("Error reading input.");
				else
					puts("Out of memory.");
			}
		fclose(openFP);
	}
	
	fclose(fp);
	
    return 11;
}
/* This file is a modification of 
	hxxp://rosettacode.org/wiki/Read_a_specific_line_from_a_file
*/

#include <stdio.h>
#include <stdlib.h>
 
#define BUF_SIZE ( 256 )
 
char *get_nth_line (FILE *f, int first_line_no, int last_line_no)
{
    char   buf[ BUF_SIZE ];
    size_t curr_alloc = BUF_SIZE, curr_ofs = 0;
    char   *line      = malloc( BUF_SIZE );
    int    in_line    = last_line_no == 1;
    size_t bytes_read;
 
    /* Illegal to ask for a line before the first one. */
    if ( first_line_no < 1 )
        return NULL;
 
    /* Handle out-of-memory by returning NULL */
    if ( !line )
        return NULL;
 
    /* Scan the file looking for newlines */
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
 
                    if ( !line )    /* out of memory? */
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
 
    /* Didn't find the line? */
    if ( (last_line_no - first_line_no) != 0 ) 
    {
        free( line );
        return NULL;
    }
 
    /* Resize allocated buffer to what's exactly needed by the string 
       and the terminating NUL character.  Note that this code *keeps*
       the terminating newline as part of the string. 
     */
    line = realloc( line, curr_ofs + 1 );
 
    if ( !line ) /* out of memory? */
        return NULL;
 
    /* Add the terminating NUL. */
    line[ curr_ofs ] = '\0';
 
    /* Return the line.  Caller is responsible for freeing it. */
    return line;
}
 

int main( int argc, char *argv[] )
{
	if(argc != 4)
	{
		fprintf(stderr, "Usage: line_read FILE NAME First_line Last_line\n");
		return -1;
	}
	
	FILE *fp = fopen(argv[1], "r");
    char *line_bw = get_nth_line( fp, atoi(argv[2]),
								atoi(argv[3]));

    if ( line_bw )
    {
        printf("The line between Text is:\n%s\n", line_bw );
        free( line_bw );
    } else
    {
        printf("Did not find the 7th line of input.  Reason:  ");
        if ( feof( stdin ) )
            puts("End of file reached.");
        else if ( ferror( stdin ) )
            puts("Error reading input.");
        else
            puts("Out of memory.");
    }
 
    return 0;
}
#include <stdio.h>

//int main()

int help_menu()
{
	char ex_prog;
	
	  system ("clear");
	  printf ("\n\n\n");
	  printf ("\t\t*-----------------------------------------------------------------------------------------------*\n");
	
	  printf ("\t\t| SHORTED PATH OBJECT, is a compound program. It depend and run with library \"readosm\".         |\n");
	  printf ("\t\t| SHORTED PATH OBJECT, takes user input for an object and if that object is already configured. |\n");
	
	  printf ("\t\t*-----------------------------------------------------------------------------------------------*\n");
	
	  printf ("\n\n");
	  printf ("  How to configure the program?\n");
	  printf ("  --------------------------------");
	  printf ("\n\n");
	  printf ("  To configure the program, you need to download .osm file from www.openstreetmap.com or recommended repository.\n");
	  printf ("  Rename it nms.osm and upload the file in programs host directory.\n\n");
	
	  printf ("  The program first splitting the main nms.osm file by node, way and relation.\n" );
	  printf ("  Which is the reason to parse comparatively smaller file than a big one.\n\n");
			
	  printf ("  Then, the program will read from prog.conf file for given object name/s and\n");
	  printf ("  extract respective object information from splitted files.\n\n");
				
	  printf ("  After splitting respective information, the program will create \n");
	  printf ("  readosm library readable XML files for each object name given in prog.conf.\n\n");
			
	  printf ("  Once all parsing and recreating of all given object XML are finished, the program will ready to use.\n");
	
	  printf ("\n\n");
	
	  printf ("  How to edit the program?\n");
	  printf ("  ---------------------------\n");
	  printf ("\n");
	
	  printf ("  If the prog.conf file is empty, then select Edit / Update program.\n\n");
	
	  printf ("  To edit / update the program, select 2 and Enter.");
	  printf (" Program will open the prog.conf file.\n\n  Type your desired ");
	  printf (" objects name / keyword that you wish to use to find nearest one. (e.g. supermarket, police, restaurant, hospital etc.)\n\n");
	
	  printf ("  To run the program select RUN PROGRAM, type one object keyword and RETURN.\n\n\n");
	  
	  printf ("\n\n\n\n\n");
	  
	  printf ("\t\tpress x for exit!");
	
	system ("/bin/stty raw");
	
	for (;;)
	{
		ex_prog = getchar ();
		if (ex_prog == 'x')
		{	
			fflush (stdout);
			break;
		}
	}
	
	system ("/bin/stty cooked");
	
	return 0;
			
}
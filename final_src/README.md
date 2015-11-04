      *-----------------------------------------------------------------------------------------------*
	| SHORTED PATH OBJECT, is a compound program. It depend and run with library "readosm".         |
	| SHORTED PATH OBJECT, takes user input for an object and if that object is already configured. |
	*-----------------------------------------------------------------------------------------------*


  How to configure the program?
  --------------------------------

  To configure the program, you need to download .osm file from www.openstreetmap.com or recommended repository.
  Rename it nms.osm and upload the file in programs host directory.

  The program first splitting the main nms.osm file by node, way and relation.
  Which is the reason to parse comparatively smaller file than a big one.

  Then, the program will read from prog.conf file for given object name/s and
  extract respective object information from splitted files.

  After splitting respective information, the program will create 
  readosm library readable XML files for each object name given in prog.conf.

  Once all parsing and recreating of all given object XML are finished, the program will ready to use.


  How to edit the program?
  ---------------------------

  If the prog.conf file is empty, then select Edit / Update program.

  To edit / update the program, select 2 and Enter. Program will open the prog.conf file.

  Type your desired  objects name / keyword that you wish to use to find nearest one. (e.g. supermarket, police, restaurant, hospital etc.)

  To run the program select RUN PROGRAM, type one object keyword and RETURN.

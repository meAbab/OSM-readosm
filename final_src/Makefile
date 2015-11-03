
CC = gcc
CFLAG = -g -Wall

default: spo

spo:	parse_main.o split.o only_node_parse.o tag_find_node.o \
			searched_file_create.o nd_ref_faster.o file_check.o help_menu.o 
			
		$(CC) $(CFLAG) -o spo parse_main.o split.o only_node_parse.o tag_find_node.o \
								searched_file_create.o nd_ref_faster.o file_check.o help_menu.o

		
		
parse_main.o:	parse_main.c nodeANDway.h readosm.h

		$(CC) $(CFLAG) -o parse_main.c
		
only_node_parse.o:	only_node_parse.c nodeANDway.h readosm.h
		
		$(CC) $(CFLAG) -o only_node_parse.c
		
tag_find_node.o:	tag_find_node.c nodeANDway.h readosm.h
		
		$(CC) $(CFLAG) -o tag_find_node.c
		
searched_file_create.o:	searched_file_create.h

		$(CC) $(CFLAG) -o searched_file_create.h
		
nd_ref_faster.o:	nd_ref_faster.c
		
		$(CC) $(CFLAG) -o nd_ref_faster.c
		
file_check.o:	file_check.c

		$(CC) $(CFLAG) -o file_check.c
		
help_menu.o: help_menu.c

		$(CC) $(CFLAG) -o help_menu.c

		
clean:
		$(RM) spo *.o *~

		
#gcc parse_main.c split_osm.c only_node_parse.c tag_find_node.c 
			#searched_file_create.c nd_ref_faster.c file_check.c help_menu.c -o first_check.o -lreadosm
			
			
		#gcc -Wall -Wextra prog_laufen.c calc_lon_lat.c iptoLL.c -o calc_lon_lat.o -lreadosm -l
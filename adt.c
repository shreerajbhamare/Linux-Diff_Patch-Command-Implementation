#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "file_LL.h"
void init_file(file_LL *l) {
	l->table_ID = 0;
	l->line_ID = 0;
	l->max_line = 128;                                  //i.e. max 128 lines in one table assigned
	l->max_table = 20;                                  //i.e. max 20 tables assigned
	l->arr = (char ***)malloc(sizeof(char **) * l->max_table);      //table array
	l->arr[0] = (char **)malloc(sizeof(char *) * l->max_line);      //line array (max 128 lines)
}

void append_file(file_LL *l, char *str) {
	(l->arr[l->table_ID])[l->line_ID] = (char *)malloc(sizeof(char) * 2048);     //string(character pointer)created

	strcpy((l->arr[l->table_ID])[l->line_ID], str);

	l->line_ID++;
	if(l->line_ID == l->max_line) {                                             //when the current table becomes full
		l->line_ID = 0;
		l->table_ID++;
		/*When all table get fulled this piece of code doubles
		 the size of table and reallocate memory to programme

		*/
		if(l->table_ID == l->max_table) {
			l->max_table = l->max_table * 2;
			l->arr = (char ***)realloc(l->arr, sizeof(char **) * l->max_table);
		}
		l->arr[l->table_ID] = (char **)malloc(sizeof(char *) * l->max_line);
	}
}

char *getline_file(file_LL *l, int index) {
	if(index < 0 || index >= (l->table_ID * l->max_line + l->line_ID)) // Invalid to ID access id denied.

		return NULL;

	return (l->arr[index / l->max_line])[index % l->max_line]; //Mathematical calculation for index of line to fetch
}
/*  As name suggest it brings out
    character pointer(string) specifically
    last line from created linked List.
*/
char *pop_file(file_LL *l) {
	char *str;

	if(l->line_ID == 0 && l->table_ID == 0) {
		//fprintf(stderr, "File_LL is Empty\n");
		exit(errno);

	}
	/* freeing table if table becomes empty
        on removal of last line inserted in LL
	*/
	if(l->line_ID == 0) {
		l->line_ID = l->max_line - 1;
		free(l->arr[l->table_ID]);
		l->table_ID--;
		str = l->arr[l->table_ID][l->line_ID];

	}
	else {
		str = l->arr[l->table_ID][l->line_ID - 1];
		l->line_ID--;

	}

	return str;
}


//returns the number of lines present in the list
int length_file(file_LL *l) {

	return (l->table_ID * l->max_line + l->line_ID);// calculation for total length of file LL

}

//freeing Allocated Memory
//node by node
//firstly line then table
void destroy_file_LL(file_LL *l) {
	int i, size;

	size = l->table_ID * l->max_line + l->line_ID;
	for(i = 0; i < size; i++)
		free(l->arr[i / l->max_line][i % l->max_line]);

	for(i = 0; i <= l->table_ID; i++)
		free(l->arr[i]);

	free(l->arr);
}

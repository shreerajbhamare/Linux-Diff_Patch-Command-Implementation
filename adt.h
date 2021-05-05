typedef struct file_LL {
	char ***arr;

	int table_ID; //table_ID points to the current chunk being handled

	int line_ID;  //line_ID points to the current line index being handled

	int max_table;  //max_table indicates the max number of tables the structure can handle

	int max_line;   //max_line indicates the max number of lines in one table

} file_LL;

void init_file(file_LL *);

void append_file(file_LL *, char *);

char *getline_file(file_LL *, int);

char *pop_file(file_LL *);

int length_file(file_LL *);

void destroy_file_LL(file_LL *);

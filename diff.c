#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "stack.h"
#include "queue.h"

int i, j, c[200][200];
char b[200][200];
struct stat filestat1;
struct stat filestat2;
stack s1, s2;
queue q1, q2;
int cflag;                            // special flag for checking "-c" attribute


/*
    Changes to be done for "a" attribute for Start of file_LL

*/
void start_add(char *f1[], char *f2[], int a, int b){
	int i;
	if(b == 2){
		if(cflag != 0)
			enqueue(&q2, '+');
		else{
			printf("0a1\n");
			printf("> %s", f2[0]);
		}
	}
	else{
		if(cflag != 0){
			for(i = 0; i < (b - 1); i++){
				enqueue(&q2, '+');
			}
		}
		else{
			printf("0a1,%d\n", b - 1);
			for(i = 0; i < (b - 1); i++){
				printf("> %s", f2[i]);
			}
		}
	}
}
/*
    Changes to be done for "d" attribute for Start of file_LL

*/
void start_delete(char *f1[], char *f2[], int a, int b){
	int i;
	if(a == 2){
		if(cflag != 0)
			enqueue(&q1, '-');
		else{
			printf("1d0\n");
			printf("< %s", f1[0]);
		}
	}
	else{
		if(cflag != 0){
			for(i = 0; i < (a - 1); i++){
				enqueue(&q1, '-');
			}
		}
		else{
			printf("1,%dd0\n", a - 1);
			for(i = 0; i < (a - 1); i++){
				printf("< %s", f1[i]);
			}
		}
	}
}
/*
    Changes to be done for "c" attribute for Start of file_LL

*/
void start_change(char *f1[], char *f2[], int a, int b){
	int i;
	if(a == 2 && b == 2){
		if(cflag != 0){
			enqueue(&q1, '!');
			enqueue(&q2, '!');
		}
		else{
			printf("1c1\n");
			printf("< %s", f1[0]);
			printf("---\n");
			printf("> %s", f2[0]);
		}
	}
	else if(a == 2 && b != 2){
		if(cflag != 0){
			enqueue(&q1, '!');
			for(i = 0; i < (b - 1); i++)
				enqueue(&q2, '!');
		}
		else{
			printf("1c1,%d\n", b - 1);
			printf("< %s", f1[0]);
			printf("---\n");
			for(i = 0; i < (b - 1); i++)
				printf("> %s", f2[i]);
		}
	}
	else if(a != 2 && b == 2){
		if(cflag != 0){
			enqueue(&q2, '!');
			for(i = 0; i < (a - 1); i++)
				enqueue(&q1, '!');
		}
		else{
			printf("1,%dc1\n", a - 1);
			for(i = 0; i < (a - 1); i++)
				printf("< %s", f1[i]);
			printf("---\n");
			printf("> %s", f2[0]);
		}
	}
	else if(a != 2 && b != 2){
		if(cflag != 0){
			for(i = 0; i < (a - 1); i++)
				enqueue(&q1, '!');
			for(i = 0; i < (a - 1); i++)
				enqueue(&q2, '!');
		}
		else{
			printf("1,%dc1,%d\n", a - 1, b - 1);
			for(i = 0; i < (a - 1); i++)
				printf("< %s", f1[i]);
			printf("---\n");
			for(i = 0; i < (b - 1); i++)
				printf("> %s", f2[i]);
		}
	}
}
/*
    Changes to be done for "a" attribute for mid of file
    i.e. Not at start nor at the end of file_LL
*/
void mid_add(char *f1[], char *f2[],int tempa, int tempb, int a, int b){
	if(b - tempb == 2){
		if(cflag != 0){
			enqueue(&q2, '+');
		}
		else{
			printf("%da%d\n", a - 1, b - 1);
			printf("> %s", f2[b - 2]);
		}
	}
	else{
		if(cflag != 0){
			for(i = tempb; i < b - 1; i++)
				enqueue(&q2, '+');
		}
		else{
			printf("%da%d,%d\n", a - 1, tempb + 1, b - 1);
			for(i = tempb; i < b - 1; i++)
				printf("> %s", f2[i]);
		}
	}
}
/*
    Changes to be done for "d" attribute for mid of file
    i.e. Not at start nor at the end of file_LL
*/
void mid_delete(char *f1[], char *f2[], int tempa, int tempb, int a, int b){
	if(a - tempa == 2){
		if(cflag != 0){
			enqueue(&q1, '-');
		}
		else{
			printf("%dd%d\n", a - 1, b - 1);
			printf("< %s", f1[a - 2]);
		}
	}
	else{
		if(cflag != 0){
			for(i = tempa; i < a - 1; i++)
				enqueue(&q1, '-');
		}
		else{
			printf("%d,%dd%d\n", tempa + 1, a - 1, b - 1);
			for(i = tempa; i < a - 1; i++)
				printf("< %s", f1[i]);
		}
	}
}
/*
    Changes to be done for "c" attribute for mid of file
    i.e. Not at start nor at the end of file_LL
*/
void mid_change(char *f1[], char *f2[], int tempa, int tempb, int a, int b){
	if(a - tempa == 2 && b - tempb == 2){
		if(cflag != 0){
			enqueue(&q1, '!');
			enqueue(&q2, '!');
		}
		else{
			printf("%dc%d\n", a - 1, b - 1);
			printf("< %s", f1[a - 2]);
			printf("---\n");
			printf("> %s", f2[b - 2]);
		}
	}
	else if(a - tempa != 2 && b - tempb == 2){
		if(cflag != 0){
			for(i = tempa; i < a - 1; i++)
				enqueue(&q1, '!');
			enqueue(&q2, '!');
		}
		else{
			printf("%d,%dc%d\n", tempa + 1, a - 1, b - 1);
			for(i = tempa; i < a - 1; i++)
				printf("< %s", f1[i]);
			printf("---\n");
			printf("> %s", f2[b - 2]);
		}
	}
	else if(a - tempa == 2 && b - tempb != 2){
		if(cflag != 0){
			for(i = tempb; i < b - 1; i++)
				enqueue(&q2, '!');
			enqueue(&q1, '!');
		}
		else{
			printf("%dc%d,%d\n", a - 1, tempb + 1, b - 1);
			printf("< %s", f1[i]);
			printf("---\n");
			for(i = tempb; i < b - 1; i++)
				printf("> %s", f2[i]);
		}
	}
	else{
		if(cflag != 0){
			for(i = tempa; i < a - 1; i++)
				enqueue(&q1, '!');
			for(i = tempb; i < b - 1; i++)
				enqueue(&q2, '!');
		}
		else{
			printf("%d,%dc%d,%d\n", tempa + 1, a - 1, tempb + 1, b - 1);
			for(i = tempa; i < a - 1; i++)
				printf("< %s", f1[i]);
			printf("---\n");
			for(i = tempb; i < b - 1; i++)
				printf("> %s", f2[i]);
		}
	}
}
/*
    "a" attribute changes done at end of file_LL
*/
void end_add(char *f1[], char *f2[], int n, int a, int b){
	int i;
	if(b == n - 1){
		if(cflag != 0){
			enqueue(&q2, '+');
		}
		else{
			printf("%da%d\n", a, n);
			printf("> %s", f2[n - 1]);
		}
	}
	else{
		if(cflag != 0){
			for(i = b; i < n; i++)
				enqueue(&q2, '+');
		}
		else{
			printf("%da%d,%d\n", a, b + 1, n);
			for(i = b; i < n; i++){
				printf("> %s", f2[i]);
			}
		}
	}
}
/*
    "d" attribute changes done at end of file_LL
*/
void end_delete(char *f1[], char *f2[], int m, int a, int b){
	int i;
	if(a == m - 1){
		if(cflag != 0){
			enqueue(&q1, '-');
		}
		else{
			printf("%dd%d\n", m, b);
			printf("< %s", f1[m - 1]);
		}
	}
	else{
		if(cflag != 0){
			for(i = a; i < m; i++)
				enqueue(&q1, '-');
		}
		else{
			printf("%d,%dd%d\n", a + 1, m, b);
			for(i = a; i < m; i++){
				printf("< %s", f1[i]);
			}
		}
	}
}
/*
    "c" attribute changes done at end of file_LL
*/

void end_change(char *f1[], char *f2[], int m, int n, int a, int b){
	int i;
	if(a == m - 1 && b == n - 1){
		if(cflag != 0){
			enqueue(&q1, '!');
			enqueue(&q2, '!');
		}
		else{
			printf("%dc%d\n", m, n);
			printf("< %s", f1[m - 1]);
			printf("---\n");
			printf("> %s", f2[n - 1]);
		}
	}
	else if(a == m - 1 && b != n - 1){
		if(cflag != 0){
			enqueue(&q1, '!');
			for(i = b; i < n; i++)
				enqueue(&q2, '!');
		}
		else{
			printf("%dc%d,%d\n", m, b + 1, n);
			printf("< %s", f1[m - 1]);
			printf("---\n");
			for(i = b; i < n; i++)
				printf("> %s", f2[i]);
		}
	}
	else if(a != m - 1 && b == n - 1){
		if(cflag != 0){
			enqueue(&q2, '!');
			for(i = a; i < m; i++)
				enqueue(&q1, '!');
		}
		else{
			printf("%d,%dc%d\n", a + 1, m, n);
			for(i = a; i < m; i++)
				printf("< %s", f1[i]);
			printf("---\n");
			printf("> %s", f2[n - 1]);
		}
	}
	else if(a != m - 1 && b != n - 1){
		if(cflag != 0){
			for(i = a; i < m; i++)
				enqueue(&q1, '!');
			for(i = b; i < n; i++)
				enqueue(&q2, '!');

		}
		else{
			printf("%d,%dc%d,%d\n", a + 1, m, b + 1, n);
			for(i = a; i < m; i++)
				printf("< %s", f1[i]);
			printf("---\n");
			for(i = b; i < n; i++)
				printf("> %s", f2[i]);
		}
	}
}
/*
    Supportive function fir "change" i.e. "c" symbol
    to print from which line from file_1 to be changed
    So, that to match particular set of lines from file_2

    i.e. 2,3c4
    Description - 2nd and 3rd line from file_1 to be changes to match with
                  4th line of file_2

*/
void change_support(char *f1[], char *f2[], int m, int n){
	if(cflag != 0){
		for(i = 0; i < m; i++)
			enqueue(&q1, '!');
		for(i = 0; i < n; i++)
			enqueue(&q2, '!');
	}
	else{
		if(m != 1 && n != 1)
			printf("1,%dc1,%d\n", m, n);
		else if(m == 1 && n != 1)
			printf("1c1,%d\n", n);
		else if(m != 1 && n == 1)
			printf("1,%dc1\n", m);
		else if(m == 1 && n == 1)
			printf("1c1\n");
		for(i = 0; i < m; i++)
			printf("< %s", f1[i]);
		printf("---\n");
		for(i = 0; i < n; i++)
			printf("> %s", f2[i]);
	}
}
/*
    Testing conditions for add, change, delete options

    Special Symbol

    a : add
    c : change
    d : delete

*/
void opt_a_c_d(char *f1[],char *f2[],int m,int n){			
	int a, b, flag = 0, tempa, tempb;
	if(isempty(&s1)){
		if(m != 0 && n != 0){
			change_support(f1, f2, m, n);
		}
		else if(m != 0 && n == 0){
			start_delete(f1, f2, m + 1, n + 1);
		}
		else if(m == 0 && n != 0){
			start_add(f1, f2, m + 1, n + 1);
		}
	}
	else{
		while(!isempty(&s1)){
			a = pop(&s1);
			b = pop(&s2);
				if(a == 1 && b == 1 && flag == 0){
					flag++;
				}
				else if(a == 1 && b != 1 && flag == 0){
					flag++;
					start_add(f1, f2, a, b);
				}
				else if(a != 1 && b == 1 && flag == 0){
					flag++;
					start_delete(f1, f2, a, b);
				}
				else if(a != 1 && b != 1 && flag == 0){
					flag++;
					start_change(f1, f2, a, b);
				}
				else if(flag != 0){
					if(a != tempa + 1 && b == tempb + 1){
						mid_delete(f1, f2, tempa, tempb, a, b);
					}
					else if(a == tempa + 1 && b != tempb + 1){
						mid_add(f1, f2, tempa, tempb, a, b);
					}
					else if(a != tempa + 1 && b != tempb + 1){
						mid_change(f1, f2, tempa, tempb, a, b);
					}
				}
			tempa = a;
			tempb = b;
		}
		if(a != m && b == n){
			end_delete(f1, f2, m, a, b);
		}
		else if(a == m && b != n){
			end_add(f1, f2, n, a, b);
		}
		else if(a != m && b != n){
			end_change(f1, f2, m, n, a, b);
		}
	}
}
/*
    attribute "-u" implemented for both file at a time
    -u   output NUM (default 3) lines of unified context
*/
void option_u(char *f1[], char *f2[], int i, int j){
	if(i > 0 && j > 0 && b[i][j] == 'd'){
		option_u(f1, f2, i - 1, j - 1);
		printf(" %s", f1[j - 1]);
	}
	else if(j > 0 && (i == 0 || b[i][j] == 'l')){
		option_u(f1, f2, i, j - 1);
		printf("-%s", f1[j - 1]);
	}
	else if(i > 0 && (j == 0 || b[i][j] == 'u')){
		option_u(f1, f2, i - 1, j);
		printf("+%s", f2[i - 1]);
	}
}
/*
    attribute "-c" implemented for first file
    -c   output NUM (default 3) lines of copied context
*/

void option_c_1(char *f1[], char *f2[], int i, int j){
	if(i > 0 && j > 0 && b[i][j] == 'd'){
		option_c_1(f1, f2, i - 1, j - 1);
		printf("  %s", f1[j - 1]);
	}
	else if(j > 0 && (i == 0 || b[i][j] == 'l')){
		option_c_1(f1, f2, i, j - 1);
		char ch = dequeue(&q1);
		printf("%c %s", ch, f1[j - 1]);
	}
	else if(i > 0 && (j == 0 || b[i][j] == 'u')){
		option_c_1(f1, f2, i - 1, j);
	}
}
/*
    attribute "-c" implemented for second file
    -c   output NUM (default 3) lines of copied context
*/
void option_c_2(char *f1[], char *f2[], int i, int j){
	if(i > 0 && j > 0 && b[i][j] == 'd'){
		option_c_2(f1, f2, i - 1, j - 1);
		printf("  %s", f1[j - 1]);
	}
	else if(j > 0 && (i == 0 || b[i][j] == 'l')){
		option_c_2(f1, f2, i, j - 1);
	}
	else if(i > 0 && (j == 0 || b[i][j] == 'u')){
		option_c_2(f1, f2, i - 1, j);
		char ch = dequeue(&q2);
		printf("%c %s", ch, f2[i - 1]);
	}
}
/*
    Main Algorithm to find commomn subsequence of string

*/
void LCS_file(char *f1[], char *f2[], int m, int n){
	for(i = 0; i <= n; i++)
		c[i][0] = 0;
	for(j = 0; j <= m; j++)
		c[0][j] = 0;
	for(i = 1; i <= n; i++){
		for(j = 1;j <= m; j++){
			if(strcmp(f2[i - 1], f1[j - 1]) == 0){
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 'd';
			}
			else if(c[i - 1][j] >= c[i][j - 1]){
				c[i][j] = c[i - 1][j];
				b[i][j] = 'u';
			}
			else{
				c[i][j] = c[i][j - 1];
				b[i][j] = 'l';
			}
		}
	}
}
/*
    -i   ignore case differences in file contents
*/
void LCS_option_i(char *f1[], char *f2[], int m, int n){
	for(i = 0; i <= n; i++)
		c[i][0] = 0;
	for(j = 0; j <= m; j++)
		c[0][j] = 0;
	for(i = 1; i <= n; i++){
		for(j = 1;j <= m; j++){
			if(strcasecmp(f2[i - 1], f1[j - 1]) == 0){
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 'd';
			}
			else if(c[i - 1][j] >= c[i][j - 1]){
				c[i][j] = c[i - 1][j];
				b[i][j] = 'u';
			}
			else{
				c[i][j] = c[i][j - 1];
				b[i][j] = 'l';
			}
		}
	}
}
void  diff(char *f1[], char *f2[], int i, int j){		//recursive backtracking
	int l1, l, count = 0;
	if(i > 0 && j > 0 && b[i][j] == 'd'){
		push(&s1, j);
		push(&s2, i);
		diff(f1, f2, i - 1, j - 1);
	}
	else if(j > 0 && (i == 0 || b[i][j] == 'l')){
		diff(f1, f2, i, j - 1);
	}
	else if(i > 0 && (j == 0 || b[i][j] == 'u')){
		diff(f1, f2, i - 1, j);
	}
}

int main(int argc, char *argv[]){
	char *f1[100], *f2[100], *f3[100], *f4[100], *f5[100], *f6[100];
	int m = 0, n = 0, l1, l2;
    	char str1[200], str2[200], arr1[200], arr2[200], arr3[200], arr4[200];
    	int size1 = sizeof(str1);
    	int size2 = sizeof(str2);
    	init(&s1,16);
    	init(&s2,16);
    	initq(&q1,50);
    	initq(&q2,50);
	FILE *fp1, *fp2;
	if(argc == 2){
		if((strcmp(argv[1],"--help")) == 0){
			printf("******************************************************\n\n");
			printf("Name: Shreeraj Vijay Bhamare\n");
			printf("MIS: 111903098 ; Div: 02 ; Batch: S1\n");
			printf("Project: Diff-Patch Implementation in C programming\n\n");
			printf("******************************************************\n\n");	
			printf("\t\tUsage: diff [OPTION]... FILES\n\t\tCompare FILES line by line.\n\n");
			printf("\t\t-c   output NUM (default 3) lines of copied context\n");
			printf("\t\t-u   output NUM (default 3) lines of unified context\n");
			printf("\t\t-i   ignore case differences in file contents\n");
			printf("\t\t-b   ignore changes in the amount of white space\n");
			printf("\t\t-w   ignore all white space\n");
			printf("\t\t-q   report only when files differ\n");
  			printf("\t\t-s   report when two files are the same\n");
			exit(0);
		}
		else{
			printf("diff: missing operand after '%s'\n", argv[1]);
			printf("diff: Try 'diff --help' for more information.\n");
			exit(0);
		}
	}
	else if(argc == 1){
		printf("diff: missing operand after '%s'\n", argv[0]);
		printf("diff: Try 'diff --help' for more information.\n");
		exit(0);
	}
	else if(argc == 3){
		fp1 = fopen(argv[1], "r+");
		fp2 = fopen(argv[2], "r+");
		if(fp1 == NULL){
			printf("diff: %s: No such file or directory\n", argv[1]);
			exit(0);
		}
		if(fp2 == NULL){
			printf("diff: %s: No such file or directory\n", argv[2]);
			exit(0);
		}
	}
	else if(argc == 4){
		if(strcmp(argv[1],"-u") == 0 || strcmp(argv[1],"-c") == 0 || strcmp(argv[1],"-i") == 0 || strcmp(argv[1],"-b") == 0 || strcmp(argv[1],"-w") == 0 || strcmp(argv[1],"-q") == 0 || strcmp(argv[1],"-s") == 0){
			fp1 = fopen(argv[2], "r+");
			fp2 = fopen(argv[3], "r+");
			stat(argv[2], &filestat1);
			stat(argv[3], &filestat2);
			if(fp1 == NULL){
				printf("diff: %s: No such file or directory\n", argv[2]);
				exit(0);
			}
			if(fp2 == NULL){
				printf("diff: %s: No such file or directory\n", argv[3]);
				exit(0);
			}
		}
		else{
			printf("diff: extra operand '%s'\n", argv[3]);
			printf("diff: Try 'diff --help' for more information.\n");
			exit(0);
		}

	}
	else if(argc > 4){
		printf("diff: extra operand '%s'\n", argv[3]);
		printf("diff: Try 'diff --help' for more information.\n");
		exit(0);
	}

    	while(fgets(str1, size1, fp1) != NULL){
	       	f1[m] = (char *)malloc(size1);
        	strcpy(f1[m], str1);
        	m++;
    	}
    	while(fgets(str2, size2, fp2) != NULL){
        	f2[n] = (char *)malloc(size2);
        	strcpy(f2[n], str2);
        	n++;
    	}
    	fseek(fp1, 0, SEEK_SET);
    	fseek(fp2, 0, SEEK_SET);

    	// for option b
	int a = 0;
	while(!feof(fp1)){
		char arr1[200];
		int i = 0, count = 0;
		for(char ch = fgetc(fp1); ch != EOF && ch != '\n'; ch = fgetc(fp1)){
			if(ch != ' ' && ch != '\t'){
				arr1[i++] = ch;
				count++;
			}
			else
				continue;
		}
		arr1[i] = '\0';
		f3[a] = (char *)malloc(count);
		strcpy(f3[a], arr1);
		a++;
	}

	int b = 0;
	while(!feof(fp2)){
		char arr2[200];
		int i = 0, count = 0;
		for(char ch = fgetc(fp2); ch != EOF && ch != '\n'; ch = fgetc(fp2)){
			if(ch != ' ' && ch != '\t'){
				arr2[i++] = ch;
				count++;
			}
			else
				continue;
		}
		arr2[i] = '\0';
		f4[b] = (char *)malloc(count);
		strcpy(f4[b], arr2);
		b++;
	}

	fseek(fp1, 0, SEEK_SET);
    	fseek(fp2, 0, SEEK_SET);

	//for option w
	int c = 0;
	while(!feof(fp1)){
		char arr1[200];
		int i = 0, count = 0;
		for(char ch = fgetc(fp1); ch != EOF && ch != '\n'; ch = fgetc(fp1)){
			if(!isspace(ch)){
				arr1[i++] = ch;
				count++;
			}
			else
				continue;
		}
		arr1[i] = '\0';
		f5[c] = (char *)malloc(count);
		strcpy(f5[c], arr1);
		c++;
	}

	int d = 0;
	while(!feof(fp2)){
		char arr2[200];
		int i = 0, count = 0;
		for(char ch = fgetc(fp2); ch != EOF && ch != '\n'; ch = fgetc(fp2)){
			if(!isspace(ch)){
				arr2[i++] = ch;
				count++;
			}
			else
				continue;
		}
		arr2[i] = '\0';
		f6[d] = (char *)malloc(count);
		strcpy(f6[d], arr2);
		d++;
	}

     	char t1[100], t2[100];
    	strftime(t1, 100, "%Y-%m-%d %H:%M:%S %z", localtime(&filestat1.st_mtime));		//for timestamp
    	strftime(t2, 100, "%Y-%m-%d %H:%M:%S %z", localtime(&filestat2.st_mtime));
	if(argc == 3){						//diff without options
		LCS_file(f1, f2, m, n);
		diff(f1, f2, n, m);
		opt_a_c_d(f1, f2, m, n);
	}
	else{
		if(strcmp(argv[1],"-u") == 0){			//It prints the output in +,- format with timestamp
			if(m == 0 && n == 0){
				exit(0);
			}
			else{
				printf("--- %s	%s\n", argv[2], t1);
				printf("+++ %s	%s\n", argv[3], t2);
				if(m > 1 && n > 1){
					printf("@@ -1,%d +1,%d @@\n", m, n);
				}
				else if(m == 1 && n > 1){
					printf("@@ -1 +1,%d @@\n", n);
				}
				else if(m > 1 && n == 1){
					printf("@@ -1,%d +1 @@\n", m);
				}
				else if(m == 1 && n == 1){
					printf("@@ -1 +1 @@\n");
				}
				else if(m == 0 && n > 1){
					printf("@@ -0,0 +1,%d @@\n", n);
				}
				else if(m == 0 && n == 1){
					printf("@@ -0,0 +1 @@\n");
				}
				else if(m == 1 && n == 0){
					printf("@@ -1 +0,0 @@\n");
				}
				else if(m > 1 && n == 0){
					printf("@@ -1,%d +0,0 @@\n", m);
				}
				LCS_file(f1, f2, m, n);
				option_u(f1, f2, n, m);
			}
		}
		else if(strcmp(argv[1],"-c") == 0){		//prints output for each file separately in +,- format with timestamp
			if(m == 0 && n == 0){
				exit(0);
			}
			else{
				cflag++;
				printf("*** %s	%s\n", argv[2], t1);
				printf("--- %s	%s\n", argv[3], t2);
				LCS_file(f1, f2, m, n);
				diff(f1, f2, n, m);
				opt_a_c_d(f1, f2, m, n);
				printf("***************\n");
				if(m > 1){
					printf("*** 1,%d ****\n", m);
				}
				else if(m == 1){
					printf("*** 1 ****\n");
				}
				else{
					printf("*** 0 ****\n");
				}
				option_c_1(f1, f2, n, m);
				if(n > 1){
					printf("--- 1,%d ----\n", n);
				}
				else if(n == 1){
					printf("--- 1 ----\n");
				}
				else{
					printf("--- 0 ----\n");
				}
				option_c_2(f1, f2, n, m);
			}
		}
		else if(strcmp(argv[1],"-i") == 0){		//It gives diff output by ignoring cases of letters
			LCS_option_i(f1, f2, m, n);
			diff(f1, f2, n, m);
			opt_a_c_d(f1, f2, m, n);
		}
		else if(strcmp(argv[1],"-b") == 0){		// ignores blanks and tabs
			LCS_file(f3, f4, a, b);
			diff(f1, f2, n, m);
			opt_a_c_d(f1, f2, m, n);
		}
		else if(strcmp(argv[1],"-w") == 0){		//ignores all whitespaces(space, h and v tabs, form feed, form feed)
			LCS_file(f5, f6, a, b);
			diff(f1, f2, n, m);
			opt_a_c_d(f1, f2, m, n);
		}
		else if(strcmp(argv[1],"-q") == 0){		//reports when files differ otherwise prints output
			LCS_file(f1, f2, m, n);
			diff(f1, f2, n, m);
			if(s1.i != m){
				printf("Files %s and %s differ\n", argv[2], argv[3]);
			}
			else{
				opt_a_c_d(f1, f2, m, n);
			}
		}
		else if(strcmp(argv[1],"-s") == 0){		//reports when files identical otherwise prints output
			LCS_file(f1, f2, m, n);
			diff(f1, f2, n, m);
			if(s1.i == m){
				printf("Files %s and %s are identical\n", argv[2], argv[3]);
			}
			else{
				opt_a_c_d(f1, f2, m, n);
			}
		}
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char *x[100];
	int m = 0, i, j;
    	char str1[200];
    	int size1 = sizeof(str1);
	FILE *fp1, *fp2, *fp3;
	if(argc == 1){
		printf("patch: missing operand after '%s'\n", argv[0]);
		printf("patch: Try 'diff --help' for more information.\n");
		exit(0);
	}
	else if(argc == 2){
		if((strcmp(argv[1],"--help")) == 0){
			printf("******************************************************\n\n");
			printf("Name: Shreeraj Vijay Bhamare\n");
			printf("MIS: 111903098 ; Div: 02 ; Batch: S1\n");
			printf("Project: Diff-Patch Implementation in C programming\n\n");
			printf("******************************************************\n\n\n");
			printf("\t\tUsage: patch [OPTION]... [ORIGFILE [PATCHFILE]]\n\n\n");
			exit(0);
		}
		else{
			printf("patch: missing operand after '%s'\n", argv[1]);
			printf("patch: Try 'diff --help' for more information.\n");
			exit(0);
		}
	}
	else if(argc == 3){
		fp1 = fopen("tempfile.txt", "w+");
		fp2 = fopen(argv[2], "r+");
		fp3 = fopen(argv[1], "r");
		if(fp1 == NULL){
			printf("patch: %s: No such file or directory\n", argv[1]);
			exit(0);
		}
		if(fp2 == NULL){
			printf("patch: %s: No such file or directory\n", argv[2]);
			exit(0);
		}
	}
	else if(argc > 3){
		printf("patch: extra operand '%s'\n", argv[3]);
		printf("patch: Try 'patch --help' for more information.\n");
		exit(0);
	}

    	while(fgets(str1, size1, fp2) != NULL){
	       	x[m] = (char *)malloc(size1);
        	strcpy(x[m], str1);
        	m++;
    	}
    	for(i = 3; i < m; i++){
    		if(x[i][0] == '+'){
    			int len;
    			len = strlen(x[i]);
    			for(j = 1; j < len; j++)
    				fprintf(fp1, "%c", x[i][j]);
    		}
    		else if(x[i][0] == ' '){
    			int len;
    			len = strlen(x[i]);
    			for(j = 1; j < len; j++)
    				fprintf(fp1, "%c", x[i][j]);
    		}
    		else if(x[i][0] == '-'){
    			continue;
    		}
    	}
    	char arr1[20] = "tempfile.txt";
    	char arr2[20];
    	strcpy(arr2, argv[1]);
    	int val = rename(arr1, arr2);
	/*if(val ==0){
		printf("File renamed successfully");
	}
	else
		printf("Rename failed");*/
    	printf("patching file %s\n", argv[1]);
    	fclose(fp1);
    	fclose(fp2);
    	fclose(fp3);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{  
	FILE *fptrIn;
	if ((fptrIn = fopen(argv[1],"r")) == NULL){
		printf("Error opening input file");
		// Program exits if the file pointer returns NULL.
		exit(1);
   	} 
  	FILE *fptrOut;
	if ((fptrOut = fopen("./out.bin","wb")) == NULL){
		printf("Error opening output file");		
		// Program exits if the file pointer returns NULL.
		exit(1);
	}

	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	uint32_t num1, num2;

	while ((read = getline(&line, &len, fptrIn)) != -1){
		sscanf(line, "%u\t%u\n", &num1, &num2);
		fwrite(&num1, sizeof(uint32_t), 1, fptrOut);
		fwrite(&num2, sizeof(uint32_t), 1, fptrOut);
	}
 
	fclose(fptrIn);
	fclose(fptrOut); 
  	
	return 0;
}

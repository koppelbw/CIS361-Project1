#include <stdio.h>
#include <stdlib.h>

void readFreq(float given[]){
	FILE *ifp;
	ifp = fopen("LetFreq.txt", "r");
	
	if(ifp == NULL){
		printf("Error:  Could not open LetFreq.txt!!\n");
		exit(EXIT_FAILURE);
	}

	int i;
	float freq;
	for(i = 0; i < 26; i++){
		fscanf(ifp, "%f", &freq);
		given[i] = freq;
		printf("%f", given[i]);
	}
}


int main(void){

	float *given;
	readFreq(given);


	return 0;
}

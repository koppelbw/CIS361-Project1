#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPH 26
void readFreq(float given[]){
	FILE *ifp;
	ifp = fopen("LetFreq.txt", "r");
	
	if(ifp == NULL){
		printf("Error:  Could not open LetFreq.txt!!\n");
		exit(0);	
	}

	char buf[1024];
	int cnt = 1, i = 0;
	while((fgets(buf,1024,ifp)) != NULL){
		char *tok;
		tok = strtok(buf, "\n ");
		tok = strtok(NULL, "\n ");
		given[i] = atof(tok);
		i++;
	}
}


void calcFreq(float found[]){

	FILE *ifp;
	ifp = fopen("data.out", "r");
	
	if(ifp == NULL){
		printf("Error: Could not open encrypted file data.out!");
		exit(0);
	}
	
	int charCount = 0;

	int i;
	for(i = 0; i < ALPH; i++)
		found[i] = 0;
	char tmp = fgetc(ifp);
	while(tmp != EOF){
		if(isalpha(tmp)){
			charCount++;
			tmp = toupper(tmp);
			found[tmp - 'A']++;
		}
		tmp = fgetc(ifp);
		
	}

	//for loop to divide by the total number of chars, to get the ratio of each letter
	for(i = 0; i < ALPH; i++){
		found[i] /= charCount;
	}
}

int main(void){

	float given[ALPH], found[ALPH];
	

	readFreq(given);
	calcFreq(found);
	
	int i;
	for(i = 0; i < ALPH; i++){
		printf("%d: %f\n", i, found[i]);
	}

	return 0;
}

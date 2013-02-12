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
		//buf[strlen(buf)-1] = 0;
		char *tok;
		tok = strtok(buf, "\n ");
		//cnt++;
		//if(!(cnt%2)){
		tok = strtok(NULL, "\n ");
		given[i] = atof(tok);
		i++;
		//}
		//cnt++;
	}
}


int main(void){

	float given[ALPH];
	readFreq(given);

	return 0;
}

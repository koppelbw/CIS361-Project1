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


void rotate(float given[]){

        int i;
//printf("Rotate Before\n--------\n");
 //for(i=0; i < ALPH; i++)
   //         printf("%d: %f\n",i, given[i]);

        float tmp, letterZ = given[ALPH-1];
        for(i = ALPH-1; i >= 0; i--){
                tmp = given[i-1];
                given[i] = tmp;

        }
        given[0] = letterZ;
//printf("Rotate after\n-----------\n");
  //     for(i=0; i < ALPH; i++)
    //        printf("%d: %f\n", i,given[i]);
}

float sqr(float diff){
        return diff * diff;
}

	
int findKey(float given[], float found[]){
	
	int i,j, key = 0, firstTime = 1;
	float sum = 0, lowSum;

	for(j = 0; j < ALPH; j++){
		sum = 0;	
		for(i = 0; i < ALPH; i++)
			sum += sqr(found[i] - given[i]);

		if(firstTime){
			lowSum = sum;
			firstTime = 0;
		}
	
		if(sum < lowSum){
			lowSum = sum;
			key = j;
		}

		rotate(given);
	}

	return key;
}

void decrypt(int key){

	FILE *ifp, *ofp;
	ifp = fopen("data.out", "r");
	ofp = fopen("decrypted.txt", "w");

	if ( key < 0 )
        	key = key + 26;

	char tmp = fgetc(ifp);
	while(tmp != EOF){

	   if( isupper(tmp) )
		fprintf(ofp, "%c", (tmp - key + 26 - 'A') %26 + 'A');
           else  if ( islower(tmp) )
                fprintf(ofp, "%c", (tmp - key + 26 - 'a') %26 + 'a');
           else
		fprintf(ofp, "%c", tmp);

		tmp = fgetc(ifp);
	}
}

int main(void){

	float given[ALPH], found[ALPH];
	
	readFreq(given);
	calcFreq(found);
	decrypt(findKey(given,found));
	printf("Your Decrypted file is now in the file decrypted.txt\n");	

	return 0;
}

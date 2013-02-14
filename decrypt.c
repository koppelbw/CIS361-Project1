/*Filename: decrypt.c
  Desription: This program deciphers a caeser cipher
  Date: 2/14/13
  Author: Bill Koppelberger
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPH 26

/* This function updates the given array with the letter frequencies
given in the file LetFreq.txt*/
void readFreq(float given[]){

	FILE *ifp;
	ifp = fopen("LetFreq.txt", "r");
	
	if(ifp == NULL){
		printf("Error:  Could not open LetFreq.txt!!\n");
		exit(0);	
	}

	//breaks each freq line into tokens, only grabs the numbers.
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

/*This function updates the found array with the letter frequencies
of the given text file to be deciphered*/
void calcFreq(float found[]){

	FILE *ifp;
	ifp = fopen("data.out", "r");
	
	if(ifp == NULL){
		printf("Error: Could not open encrypted file data.out!");
		exit(0);
	}
	
	int i, charCount = 0;

	//initializes found to 0's
	for(i = 0; i < ALPH; i++)
		found[i] = 0;

	//counts the number of times each letter appears in the ciphered text
	char tmp = fgetc(ifp);
	while(tmp != EOF){
		if(isalpha(tmp)){
			charCount++;
			tmp = toupper(tmp);
			found[tmp - 'A']++;
		}
		tmp = fgetc(ifp);
	}

	//updates the found array with the letter frequencies
	for(i = 0; i < ALPH; i++){
		found[i] /= charCount;
	}
}

/*This function moves every element in the given array 1 spot*/
void rotate(float given[]){

        int i;
        float tmp, letterZ = given[ALPH-1];

	//moves each element 1 spot down the array
        for(i = ALPH-1; i >= 0; i--){
                tmp = given[i-1];
                given[i] = tmp;
        }
        given[0] = letterZ;
}

/*This function calculates the square of the given float*/
float sqr(float diff){
        return diff * diff;
}

/*This function returns the Key of the cipher.*/
int findKey(float given[], float found[]){
	
	int i, j, key = 0, firstTime = 1;
	float sum = 0, lowSum;

	//tries all 26 rotations
	for(j = 0; j < ALPH; j++){
		sum = 0;	
	
		//sums the differences between the arrays
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

/*This function prints to a file the decrypted text*/
void decrypt(int key){

	FILE *ifp, *ofp;
	ifp = fopen("data.out", "r");
	ofp = fopen("decrypted.txt", "w");

	if ( key < 0 )
        	key = key + 26;

	char tmp = fgetc(ifp);
	while(tmp != EOF){

	   if( isupper(tmp) )
		fprintf(ofp, "%c", (tmp - key + ALPH - 'A') %ALPH + 'A');
           else  if ( islower(tmp) )
                fprintf(ofp, "%c", (tmp - key + ALPH - 'a') %ALPH + 'a');
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

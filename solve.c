#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void solve(int length, char* filename)
{
	//Get hold of cipher text
	FILE *ciphertextFile = fopen(filename, "rb");
	if(ciphertextFile == NULL)
	{
		fprintf(stderr, "Could not open file '%s'\n", filename);
		return;
	}

	//get number of bytes in ciphertext file
	fseek(ciphertextFile, 0, SEEK_END);
	int totalBytes = ftell(ciphertextFile);
	fseek(ciphertextFile, 0, SEEK_SET);

	//Read ciphertext into memory
	char* ciphertext = malloc(sizeof(char)*(totalBytes+1));
	int bytesRead = fread(ciphertext, sizeof(char)*(totalBytes), 1, ciphertextFile);
	if(bytesRead == 0)
	{
		fprintf(stderr, "\nUnable to read ciphertext file.\n");
		return;
	}
	ciphertext[totalBytes] = '\0';

	//Kasiski's Analysis
	printf("Kasiski Method\n==============\n");
	int numOfMatches = 0;
	int lenOfString = 4;
	int i = 0, j = 0, k = 0;
	do
	{
		numOfMatches = 0;

		for(i=0; i<totalBytes-lenOfString; i++)
		{
			//Prepare string to be searched.
			char string[lenOfString+1];
			for(j=0; j<lenOfString; j++)
				string[j] = ciphertext[i+j];
			string[j] = '\0';

			//If string contains extra characters, other than lowercase english, do not attempt to search for it
			for(j=0; j<lenOfString; j++)
				if(string[j] < 97 || string[j] > 122)
					break;
			if(j<lenOfString)
				continue;

			//Search for the string
			for(j=i+lenOfString; j<totalBytes-lenOfString; j++)
			{
				for(k=0; k<lenOfString; k++)
					if(j<totalBytes-lenOfString && string[k]==ciphertext[j+k])
						continue;
					else
						break;
				if(k==lenOfString)
				{
					numOfMatches++;

					printf("len=%d, i=%d, j=%d, j-i=%d, %s\n", lenOfString, i, j, j-i, string);
				}
			}
		}

		lenOfString++;
	}
	while(numOfMatches > 0);
	printf("len=%d, no more matches\n", lenOfString-1);

	//Avg. index of coincidence
	printf("\nAverage Index of Coincidence\n============================\n");

	int freq[26];
	for(i=0; i<26; i++)
		freq[i] = 0;
	int totalChars = 0;
	for(i=0; i<totalBytes; i++)
	{
		//lowercase english character
		if(ciphertext[i] >= 97 && ciphertext[i] <= 122)
		{
			freq[ciphertext[i]-97]++;
			totalChars++;
		}
	}

	//IC
	double IC = 0.0;
	double numerator = 0.0;
	for(i=0; i<26; i++)
		numerator += (freq[i]*(freq[i] - 1));
	IC = numerator / (double) (totalChars * (totalChars - 1));

	//Print results
	printf("L=%d\n", totalChars);
	for(i=0; i<26; i++)
		printf("f('%c')=%d\n", (97+i), freq[i]);
	printf("IC=%.8g\n", IC);
	double EIC = 0.0;
	int t = 1;
	double L = totalChars;
	double kp = 0.0658;
	double kr = 1/26.0;
	for(t=1; t<=length; t++)
	{
		EIC = 1/(t*(L-1)) * ( (L-t)*kp + (t-1)*L*kr );
		printf("t=%d, E(IC)=%.8g\n", t, EIC);
	}

	//Auto-correlation method
	printf("\nAuto-correlation Method\n=======================\n");
	int count = 0;
	for(t=1; t<=length; t++)
	{
		count = 0;

		//check how many collisions
		for(i=t; i<totalBytes; i++)
		{
			//printf("%d and %d\n", i, i-t);

			if(ciphertext[i]>=97 && ciphertext[i]<=122 && ciphertext[i]==ciphertext[i-t])
				count++;
		}

		printf("t=%d, count=%d\n", t, count);
	}
}

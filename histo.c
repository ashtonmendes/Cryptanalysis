#include<stdio.h>
#include<stdlib.h>

void generateHistogram(int period, int which, char* filename)
{
	//Get hold of cipher text
	FILE *ciphertext = fopen(filename, "rb");
	if(ciphertext == NULL)
	{
		ciphertext = stdin;
	}

	//Initialize Character frequencies
	int row=0;
	int histo[26][2];
	for(row=0; row<26; row++)
	{
		//which alphabet
		histo[row][0] = 97+row;

		//alphabet's frequency
		histo[row][1] = 0;
	}

	//Read ciphertext and compute histogram
	char* character = malloc(sizeof(char));
	int bytesRead = -1;
	int column = 0;
	which--; //'which' is 1 based index, convert to 0 based
	double totalCharInCol = 0.0;
	do
	{
		bytesRead = fread(character, 1, 1, ciphertext);

		//desired column
		if(column == which)
		{
			//lowercase english character
			if(*character >= 97 && *character <= 122)
			{
				totalCharInCol++;

				histo[(int)*character - 97][1]++;
			}
		}

		column = (column + 1) % period;
	}
	while(bytesRead != 0);

	//Sort according to descending order of frequencies
	int i=0, j=0;
	int flag = 0;
	int tempChar = 0;
	int tempFreq = 0;
	for(i=0; i<26; i++)
	{
		flag = 0;
		for(j=1; j<26; j++)
		{
			if(histo[j][1] > histo[j-1][1])
			{
				tempChar = histo[j][0];
				tempFreq = histo[j][1];

				histo[j][0] = histo[j-1][0];
				histo[j][1] = histo[j-1][1];

				histo[j-1][0] = tempChar;
				histo[j-1][1] = tempFreq;

				flag = 1;
			}
		}
		if(flag == 0)
			break;
	}

	//Print histogram
	printf("L=%d\n", (int)totalCharInCol);
	for(row=0; row<26; row++)
		printf("%c: %d (%.02f%%)\n", histo[row][0], histo[row][1], (histo[row][1]*100.0/totalCharInCol));

	free(character);
}

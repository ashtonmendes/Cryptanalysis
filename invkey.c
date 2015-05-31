#include<stdio.h>
#include<stdlib.h>

void generateInverseKey(char* keyfilename)
{
	FILE *keyfile = fopen(keyfilename, "rb");
	if(keyfile == NULL)
	{
		fprintf(stderr, "\nKeyfile could not be opened.\n");
		return;
	}

	//get number of lines in keyfile (period)
	fseek(keyfile, 0, SEEK_END);
	int period = ftell(keyfile)/27;
	fseek(keyfile, 0, SEEK_SET);

	//Initialize inverse key
	int row=0;
	int col=0;
	char invKey[period][27];
	for(row=0; row<period; row++)
		invKey[row][26] = '\0';

	//Read key into memory
	char key[period][period*27];
	char* character = malloc(sizeof(char));
	int bytesRead = -1;
	row=0;
	col=0;
	do
	{
		bytesRead = fread(character, 1, 1, keyfile);

		if(*character == '\n')
			key[row][col] = '\0';
		else
			key[row][col] = *character;

		//corrupt key file
		if(key[row][col] != '\0' && (key[row][col] < 97 || key[row][col] > 122))
		{
			fprintf(stderr, "\nKeyfile is corrupt.\n");
			return;
		}

		col = (col+1)%27;
		if(col==0)
			row++;
	}
	while(bytesRead != 0 && row<period);

	//Compute inverse key
	for(row=0; row<period; row++)
		for(col=0; col<26; col++)
		{
			invKey[row][(key[row][col])-97] = 97 + col;
		}

	//Print inverse key
	for(row=0; row<period; row++)
		printf("%s\n", invKey[row]);

	free(character);
}

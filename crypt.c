#include<stdio.h>
#include<stdlib.h>

void crypt(char* keyfilename, char* filename)
{
	//Initialize file pointers
	FILE *inputFile = fopen(filename, "rb");
	if(inputFile == NULL)
	{
		inputFile = stdin;
	}

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

	//Read key into memory
	char key[period][27];
	char* character = malloc(sizeof(char));
	int bytesRead = -1;
	int row=0;
	int col=0;
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

	//Read 1 character at a time and process using keyfile
	bytesRead = -1;
	int T = 0; //this tells us which permutation function to use from key[][], for encryption/decryption
	do
	{
		bytesRead = fread(character, 1, 1, inputFile);

		//For this assignment, break if newline encountered.
		if(*character == '\n')
			break;

		//non printable character encountered.
		if(*character < 32 || *character > 126)
		{
			fprintf(stderr, "\nThe input contains a non printable character, which cannot be processed using the keyfile. Aborting the program.\n");
			return;
		}

		//Lowercase english character
		if(*character >= 97 && *character <= 122)
		{
			printf("%c", key[T][*character - 97]);
		}
		else
		{
			printf("%c", *character);
		}

		T = (T + 1) % period; //encrypt/decrypt next character using next permutation function.
	}
	while(bytesRead != 0);
	printf("\n");

	free(character);
}

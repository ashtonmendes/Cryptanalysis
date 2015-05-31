#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "keygen.h"
#include "crypt.h"
#include "invkey.h"
#include "histo.h"
#include "solve.h"

void printUsage()
{
	fprintf(stderr, "Usage:\nhw4 keygen -p=pphrase -t=period\nhw4 crypt -k=keyfile [file]\nhw4 invkey keyfile\nhw4 histo -t=period -i=which [file]\nhw4 solve -l=max_t file\n");
}

int main(int argc, char *argv[])
{
	//Skip argv[0], which is the source file name
	argc--;
	argv++;

	if(argc <= 0)
	{
		fprintf(stderr, "Please enter commandline arguments.\n");
		printUsage();

		return EXIT_FAILURE;
	}



	//Keygen
	if(strcmp(*argv, "keygen") == 0)
	{
		//Get hold of arguments
		char* pphrase = malloc(100*sizeof(char));
		char* periodString = malloc(5*sizeof(char));
		int period = 0;

		//No, less or extra parameters for keygen
		if(argc-1 < 2 || argc-1 > 2)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		for(argc--; argc>0; argc--)
		{
			argv++;

			if(strlen(*argv) < 4)
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}

			//passphrase
			if(argv[0][0]=='-' && argv[0][1]=='p' && argv[0][2]=='=')
			{
				//Get passphrase from argv
				int i=0;
				for(i=3; i<strlen(*argv); i++)
				{
					pphrase[i-3] = argv[0][i];
				}
				pphrase[i-3] = '\0';
			}
			//period
			else if(argv[0][0]=='-' && argv[0][1]=='t' && argv[0][2]=='=')
			{
				//Get period from argv
				int i=0;
				for(i=3; i<strlen(*argv); i++)
				{
					periodString[i-3] = argv[0][i];
				}
				periodString[i-3] = '\0';

				period = strtod(periodString, NULL);

				//Check for errors
				if(period <= 0)
				{
					fprintf(stderr, "period should be a number greater than 0.\n");
					return EXIT_FAILURE;
				}
			}

			else
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}
		}

		keyGenerator(pphrase, period);

		free(pphrase);
		free(periodString);
	}



	//Crypt
	else if(strcmp(*argv, "crypt") == 0)
	{
		//Get hold of arguments
		char* keyfile = malloc(100*sizeof(char));
		char* file = malloc(100*sizeof(char));
		file[0] = '\0';

		//No or extra parameters for crypt
		if(argc-1 == 0 || argc-1 > 2)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		for(argc--; argc>0; argc--)
		{
			argv++;

			//Commanldine option encountered
			if(argv[0][0] == '-')
			{
				if(strlen(*argv) < 4)
				{
					fprintf(stderr, "Malformed command.\n");
					printUsage();
					return EXIT_FAILURE;
				}

				//passphrase
				if(argv[0][0]=='-' && argv[0][1]=='k' && argv[0][2]=='=')
				{
					//Get passphrase from argv
					int i=0;
					for(i=3; i<strlen(*argv); i++)
					{
						keyfile[i-3] = argv[0][i];
					}
					keyfile[i-3] = '\0';
				}
				else
				{
					fprintf(stderr, "Malformed command.\n");
					printUsage();
					return EXIT_FAILURE;
				}
			}

			//file
			else if(strlen(*argv) > 0)
			{
				//Get file from argv
				int i=0;
				for(i=0; i<strlen(*argv); i++)
				{
					file[i] = argv[0][i];
				}
				file[i] = '\0';
			}
		}

		crypt(keyfile, file);

		free(keyfile);
		free(file);
	}



	//Invkey
	else if(strcmp(*argv, "invkey") == 0)
	{
		//Get hold of arguments
		char* keyfile = malloc(100*sizeof(char));

		//No or extra parameters for invkey
		if(argc-1 == 0 || argc-1 > 1)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		argv++;

		//Get file from argv
		int i=0;
		for(i=0; i<strlen(*argv); i++)
		{
			keyfile[i] = argv[0][i];
		}
		keyfile[i] = '\0';

		generateInverseKey(keyfile);

		free(keyfile);
	}



	//Histo
	else if(strcmp(*argv, "histo") == 0)
	{
		//Get hold of arguments
		char* whichString = malloc(100*sizeof(char));
		int which = 0;
		char* periodString = malloc(5*sizeof(char));
		int period = 0;
		char* file = malloc(100*sizeof(char));
		*file='\0';

		//No, less or extra parameters for histo
		if(argc-1 < 2 || argc-1 > 3)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		for(argc--; argc>0; argc--)
		{
			argv++;

			//Commanldine option encountered
			if(argv[0][0] == '-')
			{
				if(strlen(*argv) < 4)
				{
					fprintf(stderr, "Malformed command.\n");
					printUsage();
					return EXIT_FAILURE;
				}

				//which
				if(argv[0][0]=='-' && argv[0][1]=='i' && argv[0][2]=='=')
				{
					//Get which from argv
					int i=0;
					for(i=3; i<strlen(*argv); i++)
					{
						whichString[i-3] = argv[0][i];
					}
					whichString[i-3] = '\0';

					which = strtod(whichString, NULL);

					//Check for errors
					if(which <= 0)
					{
						fprintf(stderr, "'which' should be a number greater than 0.\n");
						return EXIT_FAILURE;
					}
				}
				else if(argv[0][0]=='-' && argv[0][1]=='t' && argv[0][2]=='=')
				{
					//Get period from argv
					int i=0;
					for(i=3; i<strlen(*argv); i++)
					{
						periodString[i-3] = argv[0][i];
					}
					periodString[i-3] = '\0';

					period = strtod(periodString, NULL);

					//Check for errors
					if(period <= 0)
					{
						fprintf(stderr, "period should be a number greater than 0.\n");
						return EXIT_FAILURE;
					}
				}
				else
				{
					fprintf(stderr, "Malformed command.\n");
					printUsage();
					return EXIT_FAILURE;
				}
			}

			//file
			else if(strlen(*argv) > 0)
			{
				//Get file from argv
				int i=0;
				for(i=0; i<strlen(*argv); i++)
				{
					file[i] = argv[0][i];
				}
				file[i] = '\0';
			}
		}

		//Check for errors
		if(which > period)
		{
			fprintf(stderr, "'which' should be a number less than or equal to period.\n");
			return EXIT_FAILURE;
		}

		generateHistogram(period, which, file);

		free(whichString);
		free(periodString);
		free(file);
	}



	//Solve
	else if(strcmp(*argv, "solve") == 0)
	{
		//Get hold of arguments
		char* file = malloc(100*sizeof(char));
		*file='\0';
		char* lengthString = malloc(5*sizeof(char));
		int length = 0;

		//No, less or extra parameters for solve
		if(argc-1 < 2 || argc-1 > 2)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		for(argc--; argc>0; argc--)
		{
			argv++;

			//length
			if(strlen(*argv)>3 && argv[0][0]=='-' && argv[0][1]=='l' && argv[0][2]=='=')
			{
				//Get length from argv
				int i=0;
				for(i=3; i<strlen(*argv); i++)
				{
					lengthString[i-3] = argv[0][i];
				}
				lengthString[i-3] = '\0';

				length = strtod(lengthString, NULL);

				//Check for errors
				if(length <= 0)
				{
					fprintf(stderr, "length should be a number greater than 0.\n");
					return EXIT_FAILURE;
				}
			}

			//file
			else if(strlen(*argv) > 0)
			{
				//Get file from argv
				int i=0;
				for(i=0; i<strlen(*argv); i++)
				{
					file[i] = argv[0][i];
				}
				file[i] = '\0';
			}

			else
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}
		}

		if(strlen(file)==0)
		{
			fprintf(stderr, "file not provided.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		//Check for errors
		if(length <= 0)
		{
			fprintf(stderr, "length should be a number greater than 0.\n");
			return EXIT_FAILURE;
		}

		solve(length, file);

		free(file);
		free(lengthString);
	}

	else
	{
		fprintf(stderr, "Malformed command.\n");
		printUsage();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

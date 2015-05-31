#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <openssl/md5.h>

void generateKeystream(char *passphrase, double length, unsigned char *keystream)
{
	/*
	 * Begin code I did not write on my own.
	 * The following code was obtained from http://merlot.usc.edu/cs531-s15/homeworks/hw2/
	 * which is the website detailing the specs for HW2. In the section titled 'Key Generation for a Simple Stream Cipher',
	 * Professor Cheng has demonstrated code which generates a keystream using the MD5() function. I have gotten hold of the below
	 * code from there and have made modifications to it, so as to suit my requirements.
	 */

	unsigned char md5_buf[MD5_DIGEST_LENGTH];
	int md5BuffLength = strlen(passphrase) + 2 + MD5_DIGEST_LENGTH;
	char *s=malloc(md5BuffLength+1); //p contains \0 at the end

	int i=0;
	double remainingBytes = length;
	int bytesToBeWritten = 0;

	MD5((unsigned char*)passphrase, strlen(passphrase), md5_buf);

	for (;;)
	{
		sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, (unsigned char*)passphrase);

		memcpy(s, md5_buf, MD5_DIGEST_LENGTH);

		MD5((unsigned char*)s, md5BuffLength, md5_buf);

		bytesToBeWritten = sizeof(md5_buf)/2; //8
		if(remainingBytes - bytesToBeWritten < 0)
			bytesToBeWritten = remainingBytes;

		memcpy(keystream, md5_buf, bytesToBeWritten);

		remainingBytes = remainingBytes - bytesToBeWritten;

		if (++i == 100) i = 0;

		if(remainingBytes == 0) break;

		keystream+=bytesToBeWritten;
	}

	free(s);

	/*
	 * End code I did not write.
	 */
}



void keyGenerator(char* passphrase, int period)
{
	unsigned char keystream[200*period];
	unsigned int randomIntegers[50*period];

	generateKeystream(passphrase, 200*period, keystream);

	//Convert each 4-bytes of keystream into integers
	int i=0;
	int index = 0;
	for(i=0; i<200*period; i++)
	{
		if((i+1)%4==0)
		{
			randomIntegers[index] = (unsigned int)((keystream[i-3]<<24) + (keystream[i-2]<<16) + (keystream[i-1]<<8) + (keystream[i]));
			index++;
		}
	}

	//Now based on random integers, generate 'period' number of permutation functions
	int itrNum = 0;
	index = 0;
	unsigned int toSwap = 26;
	unsigned int swapWith = 0;
	char temp;
	for(itrNum = 0; itrNum < period; itrNum++)
	{
		char permutation[27] = "abcdefghijklmnopqrstuvwxyz\0";

		for(i=0; i<2; i++) //Do twice for better permutation
		{
			toSwap = 26;
			while(toSwap > 1)
			{
				swapWith = randomIntegers[index++];
				swapWith = swapWith % toSwap;

				//Perform swap operation
				if(swapWith != toSwap - 1)
				{
					temp = permutation[swapWith];
					permutation[swapWith] = permutation[toSwap-1];
					permutation[toSwap-1] = temp;
				}

				toSwap--;
			}
		}

		fprintf(stdout, "%s\n", permutation);
	}
}

hw4: hw4.o keygen.o crypt.o invkey.o histo.o solve.o
	gcc -g -Wall hw4.o keygen.o crypt.o invkey.o histo.o solve.o -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm -o hw4

hw4.o: hw4.c
	gcc -g -Wall -c hw4.c

keygen.o: keygen.c
	gcc -g -Wall -c keygen.c -I/home/scf-22/csci551b/openssl/include

crypt.o: crypt.c
	gcc -g -Wall -c crypt.c

invkey.o: invkey.c
	gcc -g -Wall -c invkey.c

histo.o: histo.c
	gcc -g -Wall -c histo.c

solve.o: solve.c
	gcc -g -Wall -c solve.c

clean:
	rm -f *.o hw4


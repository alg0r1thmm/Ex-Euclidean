#Makefile

all:Ex-Euclidean

xeuclid: 
	gcc xeuclid.c -L.. -lcrypto  -I../include/crypto -o xeuclid

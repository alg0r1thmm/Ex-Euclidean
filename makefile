#Makefile

all:xeuclid

xeuclid: 
	gcc xeuclid.c -L.. -lcrypto  -I../include/crypto -o xeuclid

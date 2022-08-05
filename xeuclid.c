#include <stdio.h> 
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM * a){
    /* Use BN_bn2hex(a) for hex string * Use BN_bn2dec(a) for decimal string */
    char * number_str = BN_bn2dec(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}


BIGNUM *XEuclid(BIGNUM *x, BIGNUM *y, const BIGNUM *a, const BIGNUM *b)
{
	BN_CTX *ctx = BN_CTX_new();
        BIGNUM *rem = BN_new();
        BIGNUM *d = BN_new();
        BIGNUM *q = BN_new();
        BIGNUM *r = BN_new();
        BIGNUM *g = BN_new();
        BIGNUM *a1 = BN_new();
        BIGNUM *b1 = BN_new();
        BIGNUM *com = BN_new();
        BIGNUM *prevx1 = BN_new();
        BIGNUM *prevy1 = BN_new();
        BIGNUM *prevx2 = BN_new();
        BIGNUM *prevy2 = BN_new();

	BN_copy(a1,a);
        BN_copy(b1,b);
        BN_dec2bn(&d, "1");
        BN_dec2bn(&rem, "1");
        BN_dec2bn(&prevx1, "0");
        BN_dec2bn(&prevx2, "1");
        BN_dec2bn(&prevy1, "1");
        BN_dec2bn(&prevy2, "0");
        BN_dec2bn(&com, "0");

	while(BN_ucmp(b1,com))
        {
                BN_div(q,rem,a1,b1,ctx);
                BN_mul(d,q,b1,ctx);
                BN_sub(r,a1,d);
                BN_mul(d,q,prevx1,ctx);
                BN_sub(x,prevx2,d);
                BN_mul(d,q,prevy1,ctx);
                BN_sub(y,prevy2,d);
                BN_copy(a1,b1);
                BN_copy(b1,r);
                BN_copy(prevx2,prevx1);
                BN_copy(prevx1,x);
                BN_copy(prevy2,prevy1);
                BN_copy(prevy1,y);
        }

        BN_copy(a1,a1);
        BN_copy(x,prevx2);
        BN_copy(y,prevy2);

	return a,b,x,y,a1;
}

/*
int BN_add(BIGNUM *r, const BIGNUM *a, const BIGNUM *b);
int BN_mul(BIGNUM *r, const BIGNUM *a, const BIGNUM *b, BN_CTX *ctx);
int BN_div(BIGNUM *dv, BIGNUM *rem, const BIGNUM *m, const BIGNUM *d, BN_CTX *ctx);
*/

int main (int argc, char *argv[])
{
        BIGNUM *a = BN_new();
        BIGNUM *b = BN_new();
        BIGNUM *x = BN_new();
        BIGNUM *y = BN_new();
        BIGNUM *gcd;

        if(argc != 3){
                printf("usage: xeuclid num1 num2");
                return -1;
        }
        BN_dec2bn(&a, argv[1]);
        BN_dec2bn(&b, argv[2]);
        gcd = XEuclid(x,y,a,b);

        printBN("(a,b) = ", gcd);
        printBN("a = ", a);
        printBN("b = ", b);
        printBN("x = ", x);
        printBN("y = ", y);
        printf("%s*(%s) + %s*(%s) = %s\n",BN_bn2dec(a),BN_bn2dec(x),BN_bn2dec(b),BN_bn2dec(y),BN_bn2dec(gcd));

        if(a != NULL) BN_free(a);
        if(b != NULL) BN_free(b);
        if(x != NULL) BN_free(x);
        if(y != NULL) BN_free(y);
        if(gcd != NULL) BN_free(gcd);

        return 0;
}

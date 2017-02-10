#include <stdio.h>
#include <string>
#include <openssl/sha.h>
#include <iostream>

using namespace std;

int main() 
{
    unsigned char digest[SHA256_DIGEST_LENGTH];
    string str = "hello world"; 
 
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, str.c_str (), str.size ());
    SHA256_Final(digest, &ctx);
 
    char mdString[SHA256_DIGEST_LENGTH*2+1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
 
    printf("SHA256 digest: %s\n", mdString);
 
	string password (mdString);

	cout << password << endl;
 
    return 0;
}

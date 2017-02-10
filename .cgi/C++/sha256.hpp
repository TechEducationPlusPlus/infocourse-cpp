#ifndef __sha256_coding
#define __sha256_coding
#include <stdio.h>
#include <string>
#include <openssl/sha.h>
#include <iostream>

using namespace std;

namespace sha256
{
	string GetHashCode (std::string str)
	{
		unsigned char digest[SHA256_DIGEST_LENGTH];
	 
		SHA256_CTX ctx;
		SHA256_Init(&ctx);
		SHA256_Update(&ctx, str.c_str (), str.size ());
		SHA256_Final(digest, &ctx);
	 
		char mdString[SHA256_DIGEST_LENGTH*2+1];
		for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
			sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
	 
		string password (mdString);

		return password;
	}
};
#endif

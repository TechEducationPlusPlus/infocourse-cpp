#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) 
{
	((string*)stream)->append((char*)ptr, 0, size*count);
	return size*count;
}

int main(void)
{
	CURL *curl;
	CURLcode res;

	/* In windows, this will init the winsock stuff */ 
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */ 
	curl = curl_easy_init();
	if(curl) 
	{
		string response;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/account/register");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "username=alexs&email=aex_tsvetanov_2002@abv.bg&display-name=AlexTsvetanov&first-name=Alex&last-name=Tsvetanov&password=ttts2002&password-confirm=ttts2002");

		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		curl_easy_cleanup(curl);
		
		cout << "POST: " << response << "\n";
	}
	curl_global_cleanup();

	return 0;
}


#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

namespace chat
{

	size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) 
	{
		((string*)stream)->append((char*)ptr, 0, size*count);
		return size*count;
	}

	string registration (string params)
	{
		CURL *curl;
		CURLcode res;

		curl_global_init(CURL_GLOBAL_ALL);

		curl = curl_easy_init();
		if(curl) 
		{
			string response;
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/account/register");
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str ());//"username=alexts&email=alex_tsvetanov_2002@abv.bg&display-name=AlexTsvetanov&first-name=Alex&last-name=Tsvetanov&password=tts2002&password-confirm=tts2002");

			res = curl_easy_perform(curl);
			if(res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(res));

			curl_easy_cleanup(curl);

//			cout << "POST: " << response << "\n";
			return response;
		}
		curl_global_cleanup();
	}
};

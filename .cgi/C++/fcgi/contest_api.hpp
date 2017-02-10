#include <iostream>
#include <string>
#include <curl/curl.h>

struct get_results
{
	static size_t WriteCallback (void *contents, size_t size, size_t nmemb, void *userp)
	{
		((std::string*)userp)->append ((char*)contents, size * nmemb);
		return size * nmemb;
	}

	static std::string to_json (std::string url)
	{
		CURL *curl;
		CURLcode res;
		std::string readBuffer;

		curl = curl_easy_init();
		if (curl) 
		{
			struct curl_slist *chunk = NULL;
			chunk = curl_slist_append (chunk, "Accept: application/json");
			chunk = curl_slist_append (chunk, "User-Agent: API");

			curl_easy_setopt (curl, CURLOPT_HTTPHEADER, chunk);
			curl_easy_setopt (curl, CURLOPT_URL, url.c_str ());
			curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt (curl, CURLOPT_WRITEDATA, &readBuffer);
			res = curl_easy_perform (curl);
			curl_easy_cleanup (curl);

//			std::cout << readBuffer << std::endl;
		}
		return readBuffer;
	}
};
/*
int main ()
{
	std::cout << get_results::to_json ("http://localhost") << "\n";
	std::cout << get_results::to_json ("http://localhost:8000/quiz/results/1") << "\n";
}
*/

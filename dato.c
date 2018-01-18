#include <stdio.h>
#include <curl/curl.h>


int main(void)
{
	CURL *curl;
	CURLcode res;
	//
	// Init Curl
	//
	curl = curl_easy_init();
	if(!curl) 
	{
		return 1;
	}
	//
	// Init parameters
	//
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.cocade.com.ar/ema/mb1.htm");
	printf("\n");
	printf("------------------------------ACA------------------------------\n");
	printf("\n");
	int n;
	scanf("%d",&n);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "_x0000_i1027");
	scanf("%d",&n);
	//
	// Execute command ( curl )
	//
	res = curl_easy_perform(curl);
	scanf("%d",&n);
	//
	// Check Errors
	//
	if(res != CURLE_OK)
	{
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
	}
	scanf("%d",&n);
	//
	// always cleanup 
	//
	curl_easy_cleanup(curl);
	return 0;
}

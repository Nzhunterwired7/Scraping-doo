#include <iostream>
#include <curl/curl.h>
#include <gumbo.h>

// Callback function for libcurl's write function
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to scrape a webpage
void scrapeWebPage(const std::string& url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        // Here, you would parse 'readBuffer' using Gumbo to extract the desired information
        std::cout << readBuffer << std::endl;
    }
}


int main() {
    std::string url = "https://scrapeme.live/shop/";
    scrapeWebPage(url);
    return 0;
}


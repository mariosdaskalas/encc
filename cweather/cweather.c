#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

int main(void) {
  CURL *curl;
  CURLcode res;
  char url[1000];
  char lat[100];
  char lon[100];
  const char *jsonData;

  printf("Please give the Latitude: ");
  scanf("%s", lat);
  printf("Please give the Longitude: ");
  scanf("%s", lon);

  FILE *fptr = fopen("api.txt", "r");
  char str[100];
  fgets(str, 100, fptr);
  fclose(fptr);

  sprintf(url, "https://api.openweathermap.org/data/2.5/weather?lat=%s&lon=%s&appid=%s", lat, lon, str);

  curl = curl_easy_init();
  if (curl) {
    struct curl_slist *headers = NULL;
    curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }

  return 0;
}
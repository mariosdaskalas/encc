#include <stdio.h>
#include <curl/curl.h>

int main(void) {
  FILE *fptr;
  CURL *curl;
  CURLcode res;
  char url[1000];
  char lat[100];
  char lon[100];

  printf("Please give the Latitude: ");
  scanf("%s", lat);
  printf("Please give the Longitude: ");
  scanf("%s", lon);

  fptr = fopen("api.txt", "r");
  char str[100];
  fgets(str, 100, fptr);
  // printf("%s\n", str);
  fclose(fptr);

  sprintf(url, "https://api.openweathermap.org/data/2.5/weather?lat=%s&lon=%s&appid=%s", lat, lon, str);

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }

  return 0;
}
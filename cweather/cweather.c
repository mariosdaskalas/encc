#include <stdio.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

int main(void) {
  CURL *curl;
  CURLcode res;
  char url[1000];
  char lat[100];
  char lon[100];
  char data[5000] = "data.json";

  printf("Please give the Latitude: ");
  scanf("%s", lat);
  printf("Please give the Longitude: ");
  scanf("%s", lon);

  FILE *fptr = fopen("api.txt", "r");
  char str[100];
  fgets(str, 100, fptr);
  // printf("%s\n", str);
  fclose(fptr);

  sprintf(url, "https://api.openweathermap.org/data/2.5/weather?lat=%s&lon=%s&appid=%s", lat, lon, str);

  curl = curl_easy_init();
  if(curl) {
    FILE *fp = fopen("data.json", "wb");
    if (fp == NULL) {
      printf("Error: Unable to open the file.\n");
      return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    curl_easy_cleanup(curl);

    // Read the file contents into a string
    char buffer[1024];
    size_t len = fread(buffer, 1, sizeof(buffer) - 1, fp);  // Subtract 1 for null terminator
    buffer[len] = '\0'; // Add null terminator
    printf("Raw data from file: %s\n", buffer);
    fclose(fp);

    // Parse the JSON data
    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
      const char *error_ptr = cJSON_GetErrorPtr();
      if (error_ptr != NULL) {
        printf("Error parsing JSON: %s\n", error_ptr);
      }
      printf("Parsed Data: %s\n", buffer); // Print the raw data for diagnostics
      return 1;
    } else {
      printf("JSON parsed successfully.\n");
    }

    // Access the JSON data
    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
    if (name == NULL) {
      printf("Key 'name' not found in the JSON.\n");
    } else if (cJSON_IsString(name) && (name->valuestring != NULL)) {
      printf("Name: %s\n", name->valuestring);
    } else {
      printf("Key 'name' is not a string or is null.\n");
    }

    // Delete the JSON object
    cJSON_Delete(json);
  }

  return 0;
}
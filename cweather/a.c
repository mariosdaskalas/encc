#include <stdio.h>
#include <cjson/cJSON.h>

int main() {
    // open the file
    FILE *fp = fopen("data.json", "r");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return 1;
    }

    // read the file contents into a string
    char buffer[2048]; // Increase buffer size for larger JSON
    int len = fread(buffer, 1, sizeof(buffer) - 1, fp);
    buffer[len] = '\0'; // Null-terminate the string
    fclose(fp);

    // parse the JSON data
    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        return 1;
    }

    // access the JSON data
    cJSON *coord = cJSON_GetObjectItemCaseSensitive(json, "coord");
    if (cJSON_IsObject(coord)) {
        cJSON *lon = cJSON_GetObjectItemCaseSensitive(coord, "lon");
        cJSON *lat = cJSON_GetObjectItemCaseSensitive(coord, "lat");
        if (cJSON_IsNumber(lon) && cJSON_IsNumber(lat)) {
            printf("Coordinates: Longitude: %.2f, Latitude: %.2f\n", lon->valuedouble, lat->valuedouble);
        }
    }

    cJSON *weather = cJSON_GetArrayItem(cJSON_GetObjectItemCaseSensitive(json, "weather"), 0);
    if (weather != NULL && cJSON_IsObject(weather)) {
        cJSON *description = cJSON_GetObjectItemCaseSensitive(weather, "description");
        if (cJSON_IsString(description) && (description->valuestring != NULL)) {
            printf("Weather: %s\n", description->valuestring);
        }
    }

    cJSON *main = cJSON_GetObjectItemCaseSensitive(json, "main");
    if (cJSON_IsObject(main)) {
        cJSON *temp = cJSON_GetObjectItemCaseSensitive(main, "temp");
        if (cJSON_IsNumber(temp)) {
            printf("Temperature: %.2f K\n", temp->valuedouble);
        }
    }

    // delete the JSON object
    cJSON_Delete(json);
    return 0;
}
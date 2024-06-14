#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <time.h>
#include "main.h"


int getListLen(char **list){
    int length = 0;
    while (list[length] != NULL) {
        length++;
    }
    return length;
}

char *selectMood() {
    srand(time(NULL));
    int random_index = rand() % getListLen(moods);

    return moods[random_index];
}


// API anahtarını okumak için yapılandırma dosyasını okuyan fonksiyon
char *readConfigFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File couldn't open!\n");
        return NULL;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char *api_key = NULL;

    while ((read = getline(&line, &len, file)) != -1) {
        if (strncmp(line, "API_KEY=", 8) == 0) {
            api_key = strdup(line + 8);
            // Yeni satır karakterini kaldır
            api_key[strcspn(api_key, "\n")] = '\0';
            break;
        }
    }

    free(line);
    fclose(file);

    return api_key; 
}

// Callback fonksiyonu
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    fwrite(contents, size, nmemb, (FILE *)userp);
    return realsize;
}

int main() {
    char *mood = selectMood();
    char url[256];  // Assuming a reasonable buffer size
    sprintf(url, "https://api.api-ninjas.com/v1/quotes?category=%s", mood);

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);

    char *api_key = readConfigFile("config.cfg");
    if (api_key == NULL) {
        fprintf(stderr, "API key not found in config file\n");
        return 1;
    }

    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        char auth_header[256];

        snprintf(auth_header, sizeof(auth_header), "X-Api-Key: %s", api_key);
        headers = curl_slist_append(headers, auth_header);

        // URL'yi doğru bir şekilde belirleme
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Başlıkları belirleme
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Yanıt verisini doğrudan stdout'a yazacak callback fonksiyonunu belirleme
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);

        // İsteği gerçekleştirme
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Temizlik
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    free(api_key);
    curl_global_cleanup();
    return 0;
}

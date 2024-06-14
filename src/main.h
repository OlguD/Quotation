#ifndef MAIN_H
#define MAIN_H


char *moods[] = {
            "age", "alone", "amazing", "anger",
            "architecture", "art", "attitude", "beauty", "best", "birthday",
            "business", "car", "change", "communication", "computers", "cool",
            "courage", "dad", "dating", "death", "design", "dreams", "education",
            "environmental", "equality", "experience", "failure", "faith", "family",
            "famous", "fear", "fitness", "food", "forgiveness", "freedom", "friendship", "funny",
            "future", "god", "good", "government", "graduation", "great", "happiness", "health",
            "history", "home", "hope", "humor", "imagination", "inspirational", "intelligence",
            "jealousy", "knowledge", "leadership", "learning", "legal", "life", "love", "marriage",
            "medical", "men", "mom", "money", "morning", "movies", "success"
        };

#include <stdlib.h>

int getListLen(char **list);
char *selectMood();
char *readConfigFile(const char *filename);
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);


#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* main_string = "tfduashiupfjaeiofghwithqiSJKFHHPIdsaIPHFJKFHQ373Y471HFUIQHFQ"

char* cryptography(char* word) {
    for(int i = 0; i < strlen(word) - 1; ++i ) {
        word = word[i] ^ main_string[i];
    }
    return word;
}

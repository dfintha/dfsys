#include "strings.h"

extern "C" size_t kstrlen(const char *string) {
    if (string == nullptr) return 0;
    size_t position;
    for (position = 0; string[position] != '\0'; ++position);
    return position;
}

extern "C" int kstrcmp(const char *first, const char *second) {
    if (kstrlen(first) == 0 && kstrlen(second) == 0) return 0;
    size_t position = 0;
    while (first[position] != '\0' && second[position] != '\0') {
        if (first[position] < second[position]) return -1;
        if (first[position] > second[position]) return +1;
        ++position;
    }
    return 0;
}

extern "C" char * kstrchr(const char *haystack, char needle) {
    if (kstrlen(haystack) == 0) return nullptr;
    for (size_t position = 0; haystack[position] != '\0'; ++position) {
        if (haystack[position] == needle) 
            return const_cast<char *>(haystack + position);
    }
    return nullptr;
}

extern "C" char * kstrstr(const char *haystack, const char *needle) {
    const size_t length = kstrlen(needle);
    bool found = false;
    for (size_t position = 0; haystack[position] != '\0'; ++position) {
        for (size_t offset = 0; offset < length; ++offset) {
            found = true;
            const size_t current = position + offset;
            if (haystack[current] == '\0') return nullptr;
            if (haystack[current] != needle[offset]) {
                found = false;
                break;
            }
        }
        if (found) return const_cast<char *>(haystack + position);
    }
    return nullptr;
}

extern "C" char * kstrcpy(char *destination, const char *source) {
    size_t position = 0;
    while (source[position] != '\0') {
        destination[position] = source[position];
        ++position;
    }
    return destination;
}

extern "C" char * kstrcat(char *destination, const char *source) {
    return kstrcpy(destination + kstrlen(destination) + 1, source);
}


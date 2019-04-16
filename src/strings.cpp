#include "strings.h"


extern "C" void kstritoa(char *destination, unsigned long number, int radix) {
    size_t i = 0;
    do {
        unsigned long temp = number % radix;
        destination[i++] = (temp < 10) ? (temp + '0') : (temp + 'A' - 10);
    } while (number /= radix);
    destination[i--] = '\0';

    for (size_t j = 0; j < i; ++j, --i) {
        unsigned long temp = destination[j];
        destination[j] = destination[i];
        destination[i] = temp;
    }
}

extern "C" size_t kstrlen(const char *string) {
    if (string == nullptr)
        return 0;

    size_t counter;
    for (counter = 0; string[counter] != '\0'; ++counter);
    return counter;
}

extern "C" int kstrcmp(const char *first, const char *second) {
    const size_t firstlen = kstrlen(first);
    const size_t secondlen = kstrlen(second);

    if (firstlen == 0 && secondlen == 0)
        return 0;
    if (firstlen < secondlen)
        return -1;
    if (secondlen < firstlen)
        return +1;

    size_t position = 0;
    while (first[position] != '\0' && second[position] != '\0') {
        if (first[position] < second[position]) return -1;
        if (first[position] > second[position]) return +1;
        ++position;
    }
    return 0;
}

extern "C" int kstrncmp(const char *first, const char *second, size_t bytes) {
    const size_t firstlen = kstrlen(first);
    const size_t secondlen = kstrlen(second);

    if (firstlen == 0 && secondlen == 0)
        return 0;
    if (firstlen < secondlen)
        return -1;
    if (secondlen < firstlen)
        return +1;

    size_t position = 0;
    while (first[position] != '\0' &&
           second[position] != '\0' &&
           position < bytes)
    {
        if (first[position] < second[position]) return -1;
        if (first[position] > second[position]) return +1;
        ++position;
    }
    return 0;
}

extern "C" char * kstrcpy(char *destination, const char *source) {
    for (size_t i = 0; source[i] != '\0'; ++i)
        destination[i] = source[i];
    return destination;
}

extern "C" char * kstrncpy(char *destination, const char *source, size_t bytes) {
    for (size_t i = 0; i < bytes; ++i)
        destination[i] = source[i];
    return destination;
}

extern "C" char * kstrcat(char *destination, const char *source) {
    kstrcpy(destination + kstrlen(destination), source);
    return destination;
}


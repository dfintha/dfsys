#include "strings.h"

internal char ictolower(char c) {
    constexpr const char letter_to_lower = 'a' - 'A';
    if (c >= 'A' && c <= 'Z')
        return (c + letter_to_lower);
    return c;
}

internal void istolower(char *s) {
    const size_t length = kstrlen(s);
    for (size_t i = 0; i < length; ++i)
        s[i] = ictolower(s[i]);
}

external void kstritoa(char *destination, unsigned long number, int radix) {
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

external size_t kstrlen(const char *string) {
    if (string == nullptr)
        return 0;

    size_t counter;
    for (counter = 0; string[counter] != '\0'; ++counter);
    return counter;
}

external int kstrcmp(const char *first, const char *second) {
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

external int kstrncmp(const char *first, const char *second, size_t bytes) {
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

external char * kstrcopy(char *destination, const char *source) {
    for (size_t i = 0; source[i] != '\0'; ++i)
        destination[i] = source[i];
    return destination;
}

external char * kstrncpy(char *destination, const char *source, size_t bytes) {
    for (size_t i = 0; i < bytes; ++i)
        destination[i] = source[i];
    return destination;
}

external char * kstrcat(char *destination, const char *source) {
    kstrcopy(destination + kstrlen(destination), source);
    return destination;
}

external void kstrformat(char *destination, const char *format, ...) {
    va_list args;
    va_start(args, format);
    kstrformatv(destination, format, args);
    va_end(args);
}

external void kstrformatv(char *destination, const char *format, va_list args) {
    bool formatted = false;
    *destination = '\0';

    while (*format != '\0') {
        const char current = *format;
        if (current == '%') {
            if (formatted) kstrappend(destination, current);
            formatted = !formatted;
            ++format;
            continue;
        }

        if (!formatted) {
            kstrappend(destination, current);
            ++format;
            continue;
        }

        switch (current) {
            case 'd': { // int
                const int value = va_arg(args, int);
                char buffer[64];
                kstritoa(buffer, (value < 0) ? (-value) : (value), 10);
                if (value < 0) kstrappend(destination, '-');
                kstrcat(destination, buffer);
                break;
            }

            case 'u': { // unsigned
                const unsigned value = va_arg(args, unsigned);
                char buffer[64];
                kstritoa(buffer, value, 10);
                kstrcat(destination, buffer);
                break;
            }

            case 'X':
            case 'x': { // unsigned 32-bit
                const uint32_t value = va_arg(args, uint32_t);
                char buffer[64];
                kstritoa(buffer, value, 16);
                const size_t numlen = kstrlen(buffer);
                if (current == 'x')
                    istolower(buffer);
                for (size_t i = numlen; i <= 8; ++i) {
                    kstrappend(destination, '0');
                }
                kstrcat(destination, buffer);
                break;
            }

            case 'c': { // char
                const char value = va_arg(args, int);
                kstrappend(destination, value);
                break;
            }

            case 's': { // const char *
                const char *value = va_arg(args, const char *);
                kstrcat(destination, value);
                break;
            }

            default:
                break;
        }

        formatted = false;
        ++format;
    }
}

external void kstrappend(char *destination, char c) {
    const size_t length = kstrlen(destination);
    destination[length] = c;
    destination[length + 1] = '\0';
}

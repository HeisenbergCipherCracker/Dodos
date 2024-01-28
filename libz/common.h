#include "settings.h"
#include "typedefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* base64_encode(const unsigned char *data, size_t input_length) {
    // Base64 encoding table
    const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Calculate the length of the encoded data
    size_t output_length = 4 * ((input_length + 2) / 3);

    // Allocate memory for the encoded data
    char *encoded_data = (char *)malloc(output_length + 1);
    if (encoded_data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    // Encode the data
    size_t i, j;
    for (i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded_data[j++] = base64_table[(triple >> 18) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 12) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 6) & 0x3F];
        encoded_data[j++] = base64_table[triple & 0x3F];
    }

    // Add padding if necessary
    for (size_t padding = 0; padding < (input_length % 3); padding++) {
        encoded_data[output_length - 1 - padding] = '=';
    }

    // Null-terminate the string
    encoded_data[output_length] = '\0';

    return encoded_data;
}
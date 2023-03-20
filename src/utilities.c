#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

bool is_standard_stream (FILE* const stream) {
    assert (stream != NULL);

    return stream == stdin || stream == stdout || stream == stderr;
}

/*
 * Discards extra input in filestream
 *
 * stream: FILE* = Filestream to read
 *
 * Pre: stream == stdin || ! is_standard_stream (stream)
 * Post: None
 * Return: None
 */
void discard_input (FILE* const stream) {
    assert (stream == stdin || ! is_standard_stream (stream));

    char temporary = '\0';

    do {
        temporary = fgetc (stream);
    } while (temporary != '\n' && temporary != EOF);
}

void throw_error (char* const message) {
    assert (message != NULL);

    printf ("Error: %s\n", message);
    exit (1);
}

void* allocate (size_t size) {
    void* memory = malloc (size);

    if (memory == NULL) {
        throw_error ("Memory allocation failed");
    }

    return memory;
}

int read_int (FILE* const stream, char* const message, int lower, int upper) {
    assert (stream == stdin || ! is_standard_stream (stream));
    assert (message != NULL);

    char* input = allocate (sizeof (int) + 1);
    char* end = NULL;
    bool error = false;
    int output = 0;

    do {
        if (error || end != NULL) {
            printf ("Invalid input.\n");

            if (stream != stdin) {
                throw_error ("Bad file input");
            }
        }

        printf ("%s [%d - %d]: ", message, lower, upper);

        if (fgets (input, sizeof (int) + 1, stream) == NULL) {
            error = true;
        } else {
            error = false;
            // Convert to int
            output = strtol (input, &end, 10);
        }

        if (! strchr (input, '\n')) {
            discard_input (stream);
        }

        if (stream != stdin) {
            printf ("%d\n", output);
        }
    // Input must start with an integer and be within bounds
    } while (error || end == input || output < lower || output > upper);

    free (input);
    return output;
}

char* read_string (FILE* const stream, char* const message, int upper) {
    assert (stream == stdin || ! is_standard_stream (stream));
    assert (message != NULL);

    char* input = allocate (upper + 1);
    char* newline = NULL;
    bool error = false;

    do {
        if (error) {
            printf ("Invalid input.\n");

            if (stream != stdin) {
                throw_error ("Bad file input");
            }
        }

        printf ("%s: ", message);

        if (fgets (input, sizeof (upper + 1), stream) == NULL) {
            error = true;
        } else {
            error = false;
        }
    } while (error);

    if (! strchr (input, '\n')) {
        discard_input (stream);
    }

    newline = strchr (input, '\n');

    // Remove newline
    if (newline != NULL) {
        *newline = '\0';
    }

    if (stream != stdin) {
        printf ("%s\n", input);
    }

    return input;
}

void replace_string (char* string, char* const pattern, char* const replacement) {
    assert (string != NULL);
    assert (pattern != NULL);
    assert (replacement != NULL);
    assert (strlen (pattern) == strlen (replacement));

    char* location = strstr (string, pattern);

    if (location == NULL) {
        printf ("Pattern '%s' not found in '%s'\n", pattern, string);
    } else {
        for (unsigned int i = 0; i < strlen (pattern); i ++) {
            location [i] = replacement [i];
        }
    }
}

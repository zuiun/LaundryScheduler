#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliary.h"

bool is_standard_stream (FILE* const stream) {
    assert (stream != NULL);

    return stream == stdin || stream == stdout || stream == stderr;
}

/*
 * Discards extra input in filestream
 *
 * stream: FILE* = Filestream to read
 * input: char* = Filestream input
 *
 * Pre: stream == stdin || ! is_standard_stream (stream)
 * Post: None
 * Return: None
 */
void discard_input (FILE* const stream, char* const input) {
    assert (stream == stdin || ! is_standard_stream (stream));

    // Check if input does not contain entire line
    if (! strchr (input, '\n')) {
        char temporary = '\0';

        do {
            temporary = fgetc (stream);
        } while (temporary != '\n' && temporary != EOF);
    }

    if (stream != stdin) {
        printf ("\n");
    }
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

    bool error = false;
    char* input = allocate (sizeof (int) + 1);
    char* end = NULL;
    int output = 0;

    do {
        if (error || end != NULL) {
            printf ("Invalid input.\n");

            if (stream != stdin) {
                throw_error ("Bad file input");
            }
        }

        printf ("%s [%d - %d]: ", message, lower, upper);

        if (fgets (input, sizeof (input), stream) == NULL) {
            error = true;
        } else {
            error = false;
            // Convert to int
            output = strtol (input, &end, 10);
        }

        discard_input (stream, input);
    // Input must start with an integer and be within bounds
    } while (error || end == input || output < lower || output > upper);

    free (input);
    return output;
}

char* read_string (FILE* const stream, char* const message, int upper) {
    assert (stream == stdin || ! is_standard_stream (stream));
    assert (message != NULL);

    bool error = false;
    char* input = allocate (upper + 1);
    char* newline = NULL;

    do {
        if (error) {
            printf ("Invalid input.\n");

            if (stream != stdin) {
                throw_error ("Bad file input");
            }
        }

        printf ("%s: ", message);

        if (fgets (input, sizeof (input), stream) == NULL) {
            error = true;
        } else {
            error = false;
        }
    } while (error);

    discard_input (stream, input);
    newline = strchr (input, '\n');

    // Remove newline
    if (newline != NULL) {
        *newline = '\0';
    }

    return input;
}

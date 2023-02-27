#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliary.h"

/*
 * Discards extra input in filestream
 *
 * stream: FILE* = Filestream to read
 * input: char* = Filestream input
 *
 * Pre: stream == stdin || stream > stderr
 * Post: None
 * Return: None
 */
void discard_input (FILE* const stream, char* const input) {
    assert (stream == stdin || stream > stderr);

    // Check if input does not contain entire line
    if (! strchr (input, '\n')) {
        char c = '\0';

        do {
            c = fgetc (stream);
        } while (c != '\n' && c != EOF);
    }
}

void throw_error (char* const message) {
    assert (message != NULL);

    printf ("%s\n", message);
    exit (1);
}

void* allocate (size_t size) {
    void* memory = malloc (size);

    if (memory == NULL) {
        throw_error ("Malloc failed");
    }

    return memory;
}

int read_int (FILE* const stream, char* const message, int lower, int upper) {
    assert (stream == stdin || stream > stderr);
    assert (message != NULL);

    bool error = false;
    char* input = allocate (sizeof (int) + 1);
    char* end = NULL;
    int output = 0;

    do {
        // Check if end has been set (by strtol ())
        if (error || end != NULL) {
            printf ("Invalid input.\n");
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
    assert (stream == stdin || stream > stderr);
    assert (message != NULL);

    bool error = false;
    char* input = allocate (upper + 1);
    char* newline = NULL;

    do {
        if (error) {
            printf ("Invalid input.\n");
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

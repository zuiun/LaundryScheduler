#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliary.h"
#include "priority_queue.h"
#include "scheduler.h"

/*
 * Handles command line arguments
 * Exits program if there is nothing to handle
 *
 * argc: int = Number of arguments
 * argv: char** = Values of arguments
 *
 * Pre: argc > 0, argv != NULL
 * Post: None
 * Return: Input filestream to open
 */
FILE* handle_arguments (int argc, char** const argv) {
    assert (argc > 0);
    assert (argv != NULL);

    FILE* stream = NULL;

    printf ("Laundry Scheduler - ");

    if (argc == 1) {
        printf ("Command Line\n\n");
        stream = stdin;
    } else if (argc == 2 && strcmp (argv [1], "help") == 0) {
        printf ("Help\n\nUsage: scheduler [help] [file <path to .txt>]\n\n");
        printf ("No arguments: Runs scheduler in command line\n");
        printf ("help: Displays this message\n");
        printf ("file: Runs scheduler on given .txt file\n");
        exit (0);
    } else if (argc == 3 && strcmp (argv [1], "file") == 0) {
        printf ("File Import\n\n");
        stream = fopen (argv [2], "r");

        if (stream == NULL) {
            throw_error ("File open failed");
        }
    } else {
        printf ("Unknown Argument\n\nRun with 'help' argument for usage information\n");
        exit (0);
    }

    return stream;
}

/*
 * Builds personal situation
 *
 * stream: FILE* = Input filestream
 *
 * Pre: stream == stdin || ! is_standard_stream (stream)
 * Post: None
 * Return: New personal situation
 */
person_t* build_person (FILE* const stream) {
    assert (stream == stdin || ! is_standard_stream (stream));

    person_t* person = allocate (sizeof (person_t));

    person->name = read_string (stream, "Name", 16);
    person->clothes_remaining = read_int (stream, "Amount of clothes remaining (days)", 0, 7);
    person->laundry_loads = read_int (stream, "Amount of laundry to do (loads)", 1, 4);
    person->load_time = read_int (stream, "Time to use one washed load (days)", 1, 4);
    return person;
}

/*
 * Builds laundry specification
 *
 * stream: FILE* = Input filestream
 *
 * Pre: stream == stdin || ! is_standard_stream (stream)
 * Post: None
 * Return: New laundry specification
 */
laundry_t* build_laundry (FILE* const stream) {
    assert (stream == stdin || ! is_standard_stream (stream));

    laundry_t* laundry = allocate (sizeof (laundry_t));

    laundry->number_people = read_int (stream, "Number to schedule (people)", 1, 16);
    laundry->people = allocate (laundry->number_people * sizeof (person_t));
    printf ("\n");

    for (int i = 0; i < laundry->number_people; i ++) {
        printf ("Person %d:\n", i + 1);
        laundry->people [i] = build_person (stream);
        printf ("\n");
    }

    return laundry;
}

/*
 * Chooses output filestream to open
 *
 * input: FILE* = Input filestream
 * path: char* = Input file path
 *
 * Pre: input == stdin || (! is_standard_stream (stream) && path != NULL)
 * Post: None
 * Return: Output filestream to open
 */
FILE* choose_output (FILE* const input, char* const path) {
    assert (input == stdin || (! is_standard_stream (input) && path != NULL));

    FILE* output = NULL;

    if (input == stdin) {
        output = stdout;
        printf ("Order:\n");
    } else {
        // Convert input file extension to output file extension
        char* file = strdup (path);
        char* extension = strstr (file, ".tst");

        fclose (input);

        if (file == NULL || extension == NULL) {
            throw_error ("Extension replacement failed");
        }

        extension [1] = 'o'; // t
        extension [2] = 'u'; // s
        output = fopen (file, "w+");
        printf ("Order in %s\n", file);
        free (file);
    }

    return output;
}

/*
 * Runs scheduling algorithm
 *
 * stream: FILE* = Output filestream
 *
 * Pre: stream == stdout || ! is_standard_stream (stream), pqueue != NULL
 * Post: None
 * Return: None
 */
void run_algorithm (FILE* const stream, pqueue_t* pqueue) {
    assert (stream == stdout || ! is_standard_stream (stream));
    assert (pqueue != NULL);

    while (pqueue->size > 0) {
        pqueue_e_t* element = dequeue (pqueue);
        person_t* person = element->data;

        fprintf (stream, "%s\n", person->name);
        person->laundry_loads --;

        if (person->laundry_loads > 0) {
            person->clothes_remaining += person->load_time;
            element->priority = person->clothes_remaining;
            enqueue (pqueue, element);
        } else {
            free_pqueue_e (element);
        }
    }
}

/*
 * Cleans up filestream and data structures
 *
 * stream: FILE* = Output filestream 
 * laundry: laundry_t* = Laundry specification
 * pqueue: pqueue_t* = Priority queue
 *
 * Pre: stream == stdout || ! is_standard_stream (stream), laundry != NULL, pqueue != NULL
 * Post: stream is closed if it is a file, laundry and pqueue are freed
 * Return: None
 */
void cleanup (FILE* const stream, laundry_t* laundry, pqueue_t* pqueue) {
    assert (stream == stdout || ! is_standard_stream (stream));
    assert (laundry != NULL);
    assert (pqueue != NULL);

    if (stream != stdout) {
        fclose (stream);
    }

    for (int i = 0; i < laundry->number_people; i ++) {
        free (laundry->people [i]->name);
        free (laundry->people [i]);
    }

    free (laundry->people);
    free (laundry);
    free_pqueue (pqueue);
}

/*
 * Runs laundry scheduler
 *
 * argc: int = Number of arguments
 * argv: char** = Values of arguments
 *
 * Pre: None
 * Post: None
 * Return: 0 if success, 1 if failure
 */
int main (int argc, char** argv) {
    FILE* stream = handle_arguments (argc, argv);
    laundry_t* laundry = build_laundry (stream);
    pqueue_t* pqueue = create_pqueue (laundry->number_people);

    for (int i = 0; i < laundry->number_people; i ++) {
        enqueue (pqueue, create_pqueue_e (laundry->people [i], laundry->people [i]->clothes_remaining));
    }

    // Unsafe pointer math, but argv [2] will not be accessed if it does not exist
    stream = choose_output (stream, argv [2]);
    // TODO: Needs testing
    // TODO: Crashes on more than one person
    run_algorithm (stream, pqueue);
    cleanup (stream, laundry, pqueue);
    return 0;
}

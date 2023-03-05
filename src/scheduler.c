#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliary.h"
#include "priority_queue.h"
#include "scheduler.h"

/*
 * Builds laundry specification
 *
 * stream: FILE* = Filestream to read
 *
 * Pre: stream == stdin || (stream != stdout && stream != stdin)
 * Post: None
 * Return: New laundry specification
 */
laundry_t* build_laundry (FILE* const stream) {
    assert (stream == stdin || (stream != stdout && stream != stdin));

    laundry_t* laundry = allocate (sizeof (laundry_t));

    laundry->number_people = read_int (stream, "Number to schedule (people)", 1, 16);
    laundry->people = allocate (laundry->number_people * sizeof (person_t));
    return laundry;
}

/*
 * Builds personal situation
 *
 * stream: FILE* = Filestream to read
 *
 * Pre: stream == stdin || (stream != stdout && stream != stdin)
 * Post: None
 * Return: New personal situation
 */
person_t* build_person (FILE* const stream) {
    assert (stream == stdin || (stream != stdout && stream != stdin));

    person_t* person = allocate (sizeof (person_t));

    person->name = read_string (stream, "Name", 16);
    person->clothes_remaining = read_int (stream, "Amount of clothes remaining (days)", 0, 7);
    person->laundry_loads = read_int (stream, "Amount of laundry to do (loads)", 1, 4);
    person->load_time = read_int (stream, "Time to use one washed load (days)", 1, 4);
    return person;
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
    FILE* stream = NULL;
    laundry_t* laundry = NULL;
    person_t** order = NULL;
    pqueue_t* pqueue = NULL;
    char file [PATH_LENGTH];
    int slots_needed = 0;

    printf ("Laundry Scheduler - ");

    if (argc == 1) {
        printf ("Command Line\n\n");
        stream = stdin;
    } else if (argc == 2 && strcmp (argv [1], "help") == 0) {
        printf ("Help\n\nUsage: scheduler [help] [file <path to .txt>]\n\n");
        printf ("No arguments: Runs scheduler in command line\n");
        printf ("help: Displays this message\n");
        printf ("file: Runs scheduler on given .txt file\n");
        return 0;
    } else if (argc == 3 && strcmp (argv [1], "file") == 0) {
        printf ("File Import\n\n");
        strcpy (file, argv [2]);
        stream = fopen (file, "r");

        if (stream == NULL) {
            throw_error ("File open failed");
        }
    } else {
        printf ("Unknown\n\nRun with 'help' argument for usage information\n");
        return 1;
    }

    // Data setup
    laundry = build_laundry (stream);
    printf ("\n");

    for (int i = 0; i < laundry->number_people; i ++) {
        printf ("Person %d:\n", i + 1);
        laundry->people [i] = build_person (stream);
        slots_needed += laundry->people [i]->laundry_loads;
        printf ("\n");
    }

    order = allocate (sizeof (person_t*) * slots_needed);
    pqueue = create_pqueue (slots_needed);

    for (int i = 0; i < laundry->number_people; i ++) {
        enqueue (pqueue, create_pqueue_e (laundry->people [i], laundry->people [i]->clothes_remaining));
    }

    // TODO: Test priority queue and algorithm
    // Algorithm
    for (int i = 0; i < slots_needed; i ++) {
        pqueue_e_t* element = dequeue (pqueue);
        person_t* person = element->backing_data;

        order [i] = person;
        person->laundry_loads --;

        if (person->laundry_loads > 0) {
            person->clothes_remaining += person->load_time;
            element->priority = person->clothes_remaining;
            enqueue (pqueue, element);
        } else {
            free (element);
        }
    }

    // Set output location
    if (stream == stdin) {
        stream = stdout;
    } else {
        fclose (stream);
        // Replace extension of input filename to get output filename
        char* extension = strstr (file, ".txt");

        if (extension == NULL) {
            throw_error ("Extension replacement failed");
        }

        *extension = '\0';
        strcat (file, "_output.txt");
        stream = fopen (file, "w+");
    }

    // Print order
    printf ("Order:\n");

    for (int i = 0; i < slots_needed; i ++) {
        fprintf (stream, "%s\n", order [i]->name);
    }

    if (stream != stdout) {
        printf ("Output in %s\n", file);
        fclose (stream);
    }

    // Freeing is unnecessary as program exits
    for (int i = 0; i < laundry->number_people; i ++) {
        free (laundry->people [i]->name);
        free (laundry->people [i]);
    }

    free (laundry->people);
    free (laundry);
    free (pqueue->elements);
    free (pqueue);
    free (order);
    return 0;
}

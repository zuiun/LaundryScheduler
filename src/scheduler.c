#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliary.h"
#include "scheduler.h"

/*
 * Builds laundry specification
 *
 * stream: FILE* = Filestream to read
 *
 * Pre: stream == stdin || (stream != stdout && stream != stdin)
 * Post: None
 * Return: Laundry specification
 */
laundry_t* build_laundry (FILE* const stream) {
    assert (stream == stdin || (stream != stdout && stream != stdin));

    laundry_t* laundry = allocate (sizeof (laundry_t));

    laundry->washer_time = read_int (stream, "Time to wash one load (hours)", 1, 24);
    laundry->dryer_time = read_int (stream, "Time to dry one load (hours)", 1, 24);
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
 * Return: Personal situation
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

    printf ("Laundry Scheduler - ");

    if (argc == 1) {
        printf ("Command Line\n\n");
        stream = stdin;
    } else if (argc == 2 && strcmp (argv [1], "help") == 0) {
        printf ("Help\n\n");
        return 0;
    } else if (argc == 3 && strcmp (argv [1], "file") == 0) {
        printf ("File Import\n\n");
        stream = fopen (argv [2], "r");

        if (stream == NULL) {
            throw_error ("File open failed");
        }
    } else {
        printf ("Unknown\nRun with 'help' argument for usage information.\n");
        return 1;
    }

    laundry = build_laundry (stream);
    printf ("\n");

    for (int i = 0; i < laundry->number_people; i ++) {
        printf ("Person %d:\n", i + 1);
        laundry->people[i] = build_person (stream);
        printf ("\n");
    }

    // TODO: Run algorithm

    if (stream != stdin) {
        fclose (stream);
    }

    // TODO: Print results

    /*
    // Freeing is unnecessary as program exits
    for (int i = 0; i < information->number_people; i ++) {
        free (information->people[i]->name);
        free (information->people[i]);
    }

    free (information->people);
    free (information);
    */
    return 0;
}

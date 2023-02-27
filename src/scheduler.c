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
 * Pre: stream == stdin || stream > stderr
 * Post: None
 * Return: Laundry specification
 */
laundry_t* build_laundry (FILE* const stream) {
    assert (stream == stdin || stream > stderr);

    laundry_t* laundry = allocate (sizeof (laundry_t));

    laundry->washer_time = read_int (stream, "Time to wash one load (hr)", 1, 24);
    laundry->dryer_time = read_int (stream, "Time to dry one load (hr)", 1, 24);
    laundry->number_people = read_int (stream, "Number of people to schedule", 1, 16);
    laundry->people = allocate (laundry->number_people * sizeof (person_t));
    return laundry;
}

/*
 * Builds personal situation
 *
 * stream: FILE* = Filestream to read
 *
 * Pre: stream == stdin || stream > stderr
 * Post: None
 * Return: Personal situation
 */
person_t* build_person (FILE* const stream) {
    assert (stream == stdin || stream > stderr);

    person_t* person = allocate (sizeof (person_t));

    person->name = read_string (stream, "Name", 16);
    person->clothes_remaining = read_int (stream, "Clothes remaining (days)", 0, 7);
    person->laundry_loads = read_int (stream, "Loads of laundry to do", 1, 4);
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
        // TODO: Open file into stream
        stream = stdin;
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

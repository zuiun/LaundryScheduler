#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxiliary.h"
#include "scheduler.h"

/*
 * Gets information necessary to produce schedule
 */
information_t* build_information (FILE* const stream) {
    assert (stream == stdin || stream > stderr);

    information_t* information = allocate (sizeof (information_t));

    information->washer_time = read_int (stream, "Washer time (hr)", 1, 24);
    information->dryer_time = read_int (stream, "Dryer time (hr)", 1, 24);
    information->number_people = read_int (stream, "Number of people", 1, 10);
    information->people = allocate (information->number_people * sizeof (person_t));
    return information;
}

person_t* build_person (FILE* const stream) {
    assert (stream == stdin || stream > stderr);

    person_t* person = allocate (sizeof (person_t));
    int day = 0;

    person->name = read_string (stream, "Name", 16);
    person->clothes_remaining = read_int (stream, "Clothes remaining (days)", 1, 7);
    person->laundry_loads = read_int (stream, "Loads of laundry (hr)", 1, 10);
    day = read_int (stream, "Day laundry is needed (Monday = 0, ..., Sunday = 6)", 0, 6);
    person->time_needed = day * 24 + read_int (stream, "Time laundry is needed (hr)", 0, 23);
    return person;
}

int main (int argc, char** argv) {
    FILE* stream = NULL;
    information_t* information = NULL;

    printf ("Laundry Scheduler - ");

    if (argc == 1) {
        printf ("Command Line\n\n");
        stream = stdin;
    } else if (argc == 2 && strcmp (argv [1], "help") == 0) {
        printf ("Help\n\n");
        return 0;
    } else if (argc == 3 && strcmp (argv [1], "file") == 0) {
        printf ("File Import\n\n");
        // Replace with file in future
        stream = stdin;
    } else {
        printf ("Unknown\nRun with 'help' argument for usage information.\n");
        return 1;
    }

    information = build_information (stream);
    printf ("\n");

    for (int i = 0; i < information->number_people; i ++) {
        printf ("Person %d:\n", i + 1);
        information->people[i] = build_person (stream);
        printf ("\n");
    }

    for (int i = 0; i < information->number_people; i ++) {
        free (information->people[i]->name);
        free (information->people[i]);
    }

    free (information);
    return 0;
}

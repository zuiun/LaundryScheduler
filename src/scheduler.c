#include <stdio.h>
#include <string.h>
#include "constants.h"

int main (int argc, char** argv) {
    if (argc == 2 && strcmp (argv[1], "test") == 0) {
        printf ("test mode\n");
    }

    printf ("washer = %d, dryer = %d\n", WASHER_TIME, DRYER_TIME);
    return 0;
}

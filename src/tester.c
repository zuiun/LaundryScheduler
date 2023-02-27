#include <stdio.h>
#include <string.h>

int main (int argc, char** argv) {
    printf ("Laundry Scheduler Tester");

    if (argc == 2 && strcmp (argv[1], "help") == 0) {
        printf ("Help\n\n");
    } else if (argc == 2 && strcmp (argv[1], "test") == 0) {
        printf ("Test Suite\n\n");
    } else if (argc == 3 && strcmp (argv[1], "test") == 0) {
        printf ("Test Case\n\n");
    } else {
        printf ("Unknown\nRun with 'help' argument for usage information.\n\n");
        return -1;
    }

    return 0;
}

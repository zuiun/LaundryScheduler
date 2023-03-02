// Maximum file path size
#define PATH_LENGTH 255

/*
 * Personal situation
 *
 * name: char* = Name of person
 * clothes_remaining: int = Amount of clothes remaining (days)
 * laundry_loads: int = Amount of laundry to do (loads)
 * load_time: int = Time to use one washed load (days)
 */
typedef struct Person {
    char* name;
    int clothes_remaining;
    int laundry_loads;
    int load_time;
} person_t;

/*
 * Laundry specification
 *
 * people: person_t** = Personal situation for scheduled people
 * number_people: int = Number to schedule (people)
 */
typedef struct Laundry {
    person_t** people;
    int number_people;
} laundry_t;

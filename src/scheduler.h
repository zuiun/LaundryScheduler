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
 * number_people: int = Number to schedule (people)
 * people: person_t** = Personal situation for scheduled people
 */
typedef struct Laundry {
    int number_people;
    person_t** people;
} laundry_t;

typedef struct Schedule {
    person_t** order;
    person_t** queue;
} schedule_t;

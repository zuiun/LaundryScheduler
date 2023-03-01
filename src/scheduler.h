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
 * washer_time: int = Time to wash one load (hours)
 * dryer_time: int = Time to dry one load (hours)
 * number_people: int = Number to schedule (people)
 * people: person_t** = Personal information for scheduled people
 */
typedef struct Laundry {
    int washer_time;
    int dryer_time;
    int number_people;
    person_t** people;
} laundry_t;

typedef struct Schedule {
    person_t** order;
    person_t** queue;
} schedule_t;
